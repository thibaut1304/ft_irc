/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 06:21:09 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/11 06:45:42 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Server.hpp"
#include "Mode.hpp"

#define __USER__ (user.getNickname().size() > 0 ? user.getNickname() : "*")

/* ========================================================================== */
/* --------------------------------- UTILS ---------------------------------- */
/* ========================================================================== */
static User * mode_get_user_ptr(Server *server, User user, std::string target_user)
{
	(void)user;
	Server::map_users::iterator  users_it  = server->_users.begin();
	Server::map_users::iterator  users_ite = server->_users.end();

	while (users_it != users_ite)
	{
		if (target_user == users_it->second.getNickname())
			return &(users_it->second);
		users_it++;
	}
	return NULL;
}

static bool mode_check_operator_log_rights(Server *server, User user, std::string target_user, size_t buffer_size)
{
	std::string msg;
	if (buffer_size == 2)
		if (user.getNickname() != target_user)
			if (server->is_server_operator(user.getNickname()) == false)
			{
				msg = ":" + NAME_V;
				msg += " 502 ";
				msg += user.getNickname() + " " ;
				msg += ":Can't view modes for other users";
				msg += "\r\n";
				send(user.getFd(), msg.c_str(), msg.length(), 0);
				return NOT_OK_;
			}
	return OK_;
}

static bool mode_check_operator_set_rights(Server *server, User user, std::string target_user, size_t buffer_size)
{
	std::string msg;
	if (buffer_size > 2)
		if (user.getNickname() != target_user)
			if (server->is_server_operator(user.getNickname()) == false)
			{
				msg = ":" + NAME_V;
				msg += " 502 ";
				msg += user.getNickname() + " " ;
				msg += ":Can't change mode for other users";
				msg += "\r\n";
				send(user.getFd(), msg.c_str(), msg.length(), 0);
				return NOT_OK_;
			}
	return OK_;
}

static void mode_send_to_all(Server *server, User user, std::string msg, std::string target_user)
{
	Server::map_users users = server->get_users();
	Server::map_users::iterator it = users.begin();
	Server::map_users::iterator ite = users.end();
	while (it != ite)
	{
		msg = ":" + user.getNickname() + "!" + user.getHostname() + "@" + user.getIp() + " :";
		msg += target_user + " ";
		msg += "has been promoted to server operator\r\n";
		if (it->second.getNickname() != user.getNickname())
			send(it->second.getFd(), msg.c_str(), msg.length(), 0);
		it++;
	}
}

/* ========================================================================== */
/* ------------------------------- MODE QUERY ------------------------------- */
/* ========================================================================== */

bool mode_user_log(Server *server, User user, size_t buffer_size, std::string target_user)
{
	if (buffer_size != 2)
		return false;

	std::string msg = "";
	User * userptr = mode_get_user_ptr(server, user, target_user);

	msg += ":" + NAME_V;
	msg += " 221 ";
	msg += user.getNickname() + " " ;
	msg += ":+";

	msg += userptr->get_is_invisible()          ? 'i' : char(0);
	msg += userptr->get_receive_server_notice() ? 's' : char(0);
	msg += userptr->get_receive_wallops()       ? 'w' : char(0);
	msg += userptr->get_is_operator()           ? 'o' : char(0);
	msg += "\r\n";

	send(user.getFd(), msg.c_str(), msg.length(), 0);
	return true;
}

/* ========================================================================== */
/* ------------------------------- MODE EXEC -------------------------------- */
/* ========================================================================== */
#define GET_SET(a, b) if(a == toggle) return false; else return (b, true)

static bool user_mode_w(bool toggle, User * U_) { GET_SET(U_->get_receive_wallops(),       U_->set_receive_wallops       (toggle) ); }
static bool user_mode_s(bool toggle, User * U_) { GET_SET(U_->get_receive_server_notice(), U_->set_receive_server_notice (toggle) ); }
static bool user_mode_i(bool toggle, User * U_) { GET_SET(U_->get_is_invisible(),          U_->set_is_invisible          (toggle) ); }
//static bool user_mode_o(bool toggle, User * U_) { GET_SET(U_->get_is_operator(),           U_->set_is_operator           (toggle) ); }

static char set_op(Server * server, User user, char mode, bool toggle)
{
	if (mode == 'o' && toggle == true)
		if (server->is_server_operator(user.getNickname()) == false)
		{
			std::string msg = "";
			msg += ":" + NAME_V;
			msg += " 481 ";
			msg += user.getNickname() + " " ;
			msg += ":Permission Denied - Only operators may set user mode o";
			msg += "\r\n";
			send(user.getFd(), msg.c_str(), msg.length(), 0);
			return char(0);
		}

	if (mode == 'o' && toggle == false)
	{
		if (server->is_server_operator(user.getNickname()) == true)
			server->_operators.erase(user.getNickname());
		else
			mode = char(0);
	}
	return mode;
}

static char set_bool_modes(Server * server, User user, char mode, bool toggle, std::string target_user)
{
	bool modified = false;
	User * userptr = mode_get_user_ptr(server, user, target_user);

	if (mode == 'w') modified = user_mode_w(toggle, userptr);
	if (mode == 's') modified = user_mode_s(toggle, userptr);
	if (mode == 'i') modified = user_mode_i(toggle, userptr);

	return modified ? mode : char(0);
}

/* ========================================================================== */
/* ---------------------------------- MAIN ---------------------------------- */
/* ========================================================================== */
void mode_user(Server* server, User user, std::string target)
{
	(void)target;
	BUFFER_           buffer      = server->_allBuff;
	BUFFER_::iterator it          = buffer.begin();
	std::string       target_user = it[1];
	std::string       msg;

	if (mode_check_operator_log_rights(server, user, target_user, buffer.size()) == NOT_OK_) { return;}
	if (mode_user_log                 (server, user, buffer.size(), target_user) == true)                 { return; }
	if (mode_check_operator_set_rights(server, user, target_user, buffer.size()) == NOT_OK_) { return;}

	std::string       modes   = it[2];                // NOTE : Cannot segault because checked above/
	bool              toggle  = mode_get_sign(modes); // Set ADD or REMOVE mode
	std::string       err_msg = "";                   // Error Message to send to clients
	std::string       arg     = "";                   // Current argument
	msg                       = toggle                ? "+" : "-"; // Message to send to clients
	char mode;

	modes = mode_trim_sign(modes);

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];

		if (mode_is_in_charset("o", mode) == true)
		{
			msg += set_op(server, user, mode, toggle);
		}
		else if (mode_is_in_charset("wsi", mode) == true)
			msg += set_bool_modes(server, user, mode, toggle, target_user);

		else
		{
			err_msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
			send(user.getFd(), err_msg.c_str(), err_msg.length(), 0);
			return ;
		}
	}
	mode_send_to_all(server, user, msg, target_user);
}
