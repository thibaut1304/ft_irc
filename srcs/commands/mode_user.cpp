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


void mode_user(Server* server, User user, std::string target)
{
	BUFFER_           buffer    = server->_allBuff;
	BUFFER_::iterator it        = buffer.begin();
	std::string       modes     = it[2];           // NOTE : Cannot segault because checked above/
	bool              toggle    = mode_get_sign(modes); // Set ADD or REMOVE mode
	std::string       msg       = toggle           ? "+" : "-"; // Message to send to clients
	std::string       err_msg   = "";              // Error Message to send to clients
	std::string       arg       = "";              // Current argument
	char mode;

	(void)target;
	modes = mode_trim_sign(modes);

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];

		if (mode_is_in_charset("iwso", mode) == true)
			msg += set_bool_modes(&user, mode, toggle);
		else
		{
			err_msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
			send(user.getFd(), err_msg.c_str(), err_msg.length(), 0);
			return ;
		}
	}

	//if (mode_is_in_charset("iwso", msg[1]) == true)
		//channel->sendToAll(&user, "MODE", msg);

}
