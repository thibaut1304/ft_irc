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
	Server::map_users::iterator  users_it  = server->getUsers().begin();
	Server::map_users::iterator  users_ite = server->getUsers().end();

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
	(void)server;
	std::string msg;
	if (buffer_size == 2)
		if (user.getNickname() != target_user)
			if (user.get_is_operator() == false)
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
	(void)server;
	std::string msg;
	if (buffer_size > 2)
		if (user.getNickname() != target_user)
			if (user.get_is_operator() == false)
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
	msg += userptr->getNickname() + " " ;
	msg += ":+";

	msg += userptr->get_is_invisible()             ? 'i' : char(0);
	msg += userptr->get_receive_server_notice()    ? 's' : char(0);
	msg += userptr->get_receive_wallops()          ? 'w' : char(0);
	msg += server->is_server_operator(target_user) ? 'o' : char(0);

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
static bool user_mode_o(bool toggle, User * U_) { GET_SET(U_->get_is_operator(),           U_->set_is_operator           (toggle) ); }

static char set_bool_modes(Server * server, User user, char mode, bool toggle, std::string target_user)
{
	bool modified = false;
	User * target_userptr = mode_get_user_ptr(server, user, target_user);

	if (mode == 'o' && toggle == true && user.get_is_operator() == false)
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

	if (mode == 'w') modified = user_mode_w(toggle, target_userptr);
	if (mode == 's') modified = user_mode_s(toggle, target_userptr);
	if (mode == 'i') modified = user_mode_i(toggle, target_userptr);
	if (mode == 'o') modified = user_mode_o(toggle, target_userptr);

	return modified ? mode : char(0);
}


static bool check_ERR_UNKNOWNMODE(User user, char mode)
{
	std::string msg;
	if (mode_is_in_charset("wsio", mode) == false)
	{
		msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}

/* ========================================================================== */
/* ---------------------------------- MAIN ---------------------------------- */
/* ========================================================================== */
void mode_user(Server* server, User user, std::string target)
{
	(void)target;
	BUFFER_           buffer      = server->get_buff();
	BUFFER_::iterator it          = buffer.begin();
	std::string       target_user = it[1];
	std::string       msg;

	if (mode_check_operator_log_rights(server, user, target_user, buffer.size()) == NOT_OK_) { return; }
	if (mode_user_log                 (server, user, buffer.size(), target_user) == true)    { return; }
	if (mode_check_operator_set_rights(server, user, target_user, buffer.size()) == NOT_OK_) { return; }

	std::string       modes   = it[2];
	bool              toggle  = mode_get_sign(modes); // Set ADD or REMOVE mode
	msg                       = toggle                ? "+" : "-"; // Message to send to clients
	char mode;

	modes = mode_trim_sign(modes);

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];
		if (check_ERR_UNKNOWNMODE(user, mode) == NOT_OK_ ) return;
		msg += set_bool_modes(server, user, mode, toggle, target_user);
	}

	if (mode_is_in_charset("owsi", msg[1])) // Checking if any modification has been made
	{
		std::string msg_to_send = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getIp() + " MODE " + target_user + " :" + msg + ("\r\n");
		send(user.getFd(), msg_to_send.c_str(), msg_to_send.length(), 0);
		if (user.getNickname() != target_user)
		{
			User * userptr = mode_get_user_ptr(server, user, target_user);
			send(userptr->getFd(), msg_to_send.c_str(), msg_to_send.length(), 0);
		}
	}
}
