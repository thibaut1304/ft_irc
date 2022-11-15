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

/* ========================================================================== */
/* --------------------------------- UTILS ---------------------------------- */
/* ========================================================================== */
static User * mode_get_user_ptr(Server *server, User user)
{
	Server::map_users::iterator  users_it  = server->_users.begin();
	Server::map_users::iterator  users_ite = server->_users.end();

	while (users_it != users_ite)
	{
		if (user.getNickname() == users_it->second.getNickname())
			return &(users_it->second);
		users_it++;
	}
	return NULL;
}

/* ========================================================================== */
/* ------------------------------- MODE QUERY ------------------------------- */
/* ========================================================================== */

bool mode_user_log(Server *server, User user, size_t buffer_size)
{
	if (buffer_size != 2)
		return false;

	std::string msg = "";
	User * userptr = mode_get_user_ptr(server, user);

	msg += ":" + NAME_V;
	msg += " 221 ";
	msg += user.getNickname() + " " ;
	msg += ":+";

	msg += userptr->get_is_invisible()          ? 'i' : char(0);
	msg += userptr->get_receive_server_notice() ? 's' : char(0);
	msg += userptr->get_receive_wallops()       ? 'w' : char(0);
	msg += userptr->get_is_operator()           ? 'o' : char(0);
	msg += "\r\n";

	send(userptr->getFd(), msg.c_str(), msg.length(), 0);
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


static char set_bool_modes(Server * server, User user, char mode, bool toggle)
{
	bool modified = false;
	User * userptr = mode_get_user_ptr(server, user);

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

	if (mode == 'w') modified = user_mode_w(toggle, userptr);
	if (mode == 's') modified = user_mode_s(toggle, userptr);
	if (mode == 'i') modified = user_mode_i(toggle, userptr);
	if (mode == 'o') modified = user_mode_o(toggle, userptr);

	return modified ? mode : char(0);
}

/* ========================================================================== */
/* ---------------------------------- MAIN ---------------------------------- */
/* ========================================================================== */
void mode_user(Server* server, User user, std::string target)
{
	(void)target;
	BUFFER_           buffer    = server->_allBuff;

	if (mode_user_log(server, user, buffer.size()) == true)
		return;

	BUFFER_::iterator it      = buffer.begin();
	std::string       modes   = it[2];                // NOTE : Cannot segault because checked above/
	bool              toggle  = mode_get_sign(modes); // Set ADD or REMOVE mode
	std::string       msg     = toggle                ? "+" : "-"; // Message to send to clients
	std::string       err_msg = "";                   // Error Message to send to clients
	std::string       arg     = "";                   // Current argument
	char mode;

	modes = mode_trim_sign(modes);

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];

		if (mode_is_in_charset("iwso", mode) == true)
			msg += set_bool_modes(server, user, mode, toggle);

		else
		{
			err_msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
			send(user.getFd(), err_msg.c_str(), err_msg.length(), 0);
			return ;
		}
	}
	notice(server , user);
}
