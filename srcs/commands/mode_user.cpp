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

#include "Server.hpp"
#include "Mode.hpp"

/* ========================================================================== */
/* ------------------------------- MODE QUERY ------------------------------- */
/* ========================================================================== */
static bool mode_user_log(User user, size_t buffer_size)
{
	if (buffer_size != 2)
		return false;

	std::string msg = "";

	msg += ":" + NAME_V;
	msg += " 221";
	msg += user.getNickname() + " " ;
	msg += " :+";

	msg += user.get_is_invisible()          ? 'i' : char(0);
	msg += user.get_receive_server_notice() ? 's' : char(0);
	msg += user.get_receive_wallops()       ? 'w' : char(0);
	msg += user.get_is_operator()           ? 'o' : char(0);
	msg += "\r\n";

	send(user.getFd(), msg.c_str(), msg.length(), 0);
	return true;
}

#define GET_SET(a, b) if(a == toggle) return false; else return (b, true)

static bool user_mode_w(bool toggle, User * U_) { GET_SET(U_->get_receive_wallops(),       U_->set_receive_wallops       (toggle) ); }
static bool user_mode_s(bool toggle, User * U_) { GET_SET(U_->get_receive_server_notice(), U_->set_receive_server_notice (toggle) ); }
static bool user_mode_i(bool toggle, User * U_) { GET_SET(U_->get_is_invisible(),          U_->set_is_invisible          (toggle) ); }
static bool user_mode_o(bool toggle, User * U_) { GET_SET(U_->get_is_operator(),           U_->set_is_operator           (toggle) ); }

static char set_bool_modes(User * user, char mode, bool toggle)
{
	bool modified = false;

	//if (mode == 'o') channel_mode_o(toggle, channel); // TODO
	if (mode == 'w') modified = user_mode_w(toggle, user);
	if (mode == 's') modified = user_mode_s(toggle, user);
	if (mode == 'i') modified = user_mode_i(toggle, user);
	if (mode == 'o') modified = user_mode_o(toggle, user);

	return modified ? mode : char(0);
}


static User * mode_get_user_ptr(Server *server, User user)
{
	Server::map_users users     = server->get_users();
	Server::map_users::iterator  users_it  = users.begin();
	Server::map_users::iterator  users_ite = users.end();

	while (users_it++ != users_ite)
		if (user.getNickname() == users_it->second.getNickname())
			return &users_it->second;
	return NULL;
}

void mode_user(Server* server, User user, std::string target)
{
	BUFFER_           buffer    = server->_allBuff;
	BUFFER_::iterator it        = buffer.begin();
	std::string       modes     = buffer.size() > 3 ? "" : it[2];           // NOTE : Cannot segault because checked above/
	bool              toggle    = mode_get_sign(modes); // Set ADD or REMOVE mode
	std::string       msg       = toggle           ? "+" : "-"; // Message to send to clients
	std::string       err_msg   = "";              // Error Message to send to clients
	std::string       arg       = "";              // Current argument
	char mode;
	User * userPtr = mode_get_user_ptr(server, user);

	(void)target;
	modes = mode_trim_sign(modes);

	if (mode_user_log(*userPtr, buffer.size()) == true)
		return;

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];

		if (mode_is_in_charset("iwso", mode) == true)
			msg += set_bool_modes(userPtr, mode, toggle);
		else
		{
			err_msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
			send(user.getFd(), err_msg.c_str(), err_msg.length(), 0);
			return ;
		}
	}
	//if (mode_is_in_charset("iwso", msg[1]) == true)
		//;
	//send (&user, "MODE", msg);
}
