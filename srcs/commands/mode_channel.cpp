/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes_channels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 06:08:41 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/11 06:17:54 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Mode.hpp"

/* ...................................................... */
/* ................. BOOL SETTERS ....................... */
/* ...................................................... */
#define C_ channel
#define G_ISAMFOC get_is_accepting_messages_from_outside_client
#define S_ISAMFOC set_is_accepting_messages_from_outside_client
#define GET_SET(a, b) if (a == toggle) return false; else return (b, true)
static bool channel_mode_p(bool toggle, Channel * C_) { GET_SET(C_->get_is_private(),          C_->set_is_private          (toggle) ); }
static bool channel_mode_s(bool toggle, Channel * C_) { GET_SET(C_->get_is_secret(),           C_->set_is_secret           (toggle) ); }
static bool channel_mode_i(bool toggle, Channel * C_) { GET_SET(C_->get_is_invite_only(),      C_->set_is_invite_only      (toggle) ); }
static bool channel_mode_t(bool toggle, Channel * C_) { GET_SET(C_->get_is_topic_unlocked(),   C_->set_is_topic_unlocked   (toggle) ); }
static bool channel_mode_m(bool toggle, Channel * C_) { GET_SET(C_->get_is_moderated(),        C_->set_is_moderated        (toggle) ); }
static bool channel_mode_v(bool toggle, Channel * C_) { GET_SET(C_->get_mute_non_moderators(), C_->set_mute_non_moderators (toggle) ); }
static bool channel_mode_n(bool toggle, Channel * C_) { GET_SET(C_->G_ISAMFOC(),               C_->S_ISAMFOC               (toggle) ); }

/* ...................................................... */
/* .................... ARG SETTERS ..................... */
/* ...................................................... */
static bool channel_mode_b(std::string new_ban_mask, Channel * C_) { if (C_->get_ban_mask()    == new_ban_mask) return false; else return (C_->set_ban_mask    (new_ban_mask), true); }
static bool channel_mode_k(std::string new_key,      Channel * C_) { if (C_->get_channel_key() == new_key)      return false; else return (C_->set_channel_key (new_key),      true); }
static bool channel_mode_l(size_t      new_limit,    Channel * C_) { if (C_->get_user_limit()  == new_limit)    return false; else return (C_->set_user_limit  (new_limit),    true); }

/* ...................................................... */
/* .................BOOL EXEC MODES ..................... */
/* ...................................................... */
static char set_bool_modes(Channel * channel, char mode, bool toggle)
{
	bool modified = false;

	//if (mode == 'o') channel_mode_o(toggle, channel); // TODO
	if (mode == 'p') modified = channel_mode_p(toggle, channel);
	if (mode == 's') modified = channel_mode_s(toggle, channel);
	if (mode == 'i') modified = channel_mode_i(toggle, channel);
	if (mode == 't') modified = channel_mode_t(toggle, channel);
	if (mode == 'm') modified = channel_mode_m(toggle, channel);
	if (mode == 'v') modified = channel_mode_v(toggle, channel);
	if (mode == 'n') modified = channel_mode_n(toggle, channel);

	return modified ? mode : char(0);
}

/* ..................................................... */
/* .................. ARG EXEC MODES ................... */
/* ..................................................... */

static char set_arg_modes(Channel* channel, char mode, std::string arg, bool toggle)
{
	bool        modified = false;
	std::string num_arg  = toggle ? arg : 0;
	arg = toggle ? arg : "";

	if (mode == 'b') modified = channel_mode_b(arg, channel);
	if (mode == 'k') modified = channel_mode_k(arg, channel);
	if (mode == 'l') modified = channel_mode_l(mode_str_to_num(num_arg), channel);

	return modified ? mode : char(0);
}

/* ...................................................... */
/* ............. CHANNEL MODE MAIN FUNCTION ............. */
/* ...................................................... */
void mode_channel(Server* server, User user, std::string target)
{
	BUFFER_           buffer    = server->_allBuff;
	BUFFER_::iterator it        = buffer.begin();
	BUFFER_::iterator first_arg = it + 3;          // Pointer to the first argument, right after modes
	std::string       modes     = it[2];           // NOTE : Cannot segault because checked above/
	Channel           *channel  = server->getChannel(target);
	bool              toggle    = mode_get_sign(modes); // Set ADD or REMOVE mode
	std::string       msg       = toggle           ? "+" : "-"; // Message to send to clients
	std::string       err_msg   = "";              // Error Message to send to clients
	std::string       arg       = "";              // Current argument
	int               arg_index = 0;               // Keeps track of arguments
	char mode;

	modes = mode_trim_sign(modes);

	/////////////////////// TODO delete
	if (Debug) __debug_modes(channel, "Before");
	/////////////////////// TODO delete

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];

		/* ................... BOOL MODES ................... */
		if (mode_is_in_charset("opsitnvm", mode) == true)
			msg += set_bool_modes(channel, mode, toggle);

		/* ................... DATA MODES ................... */
		else if (mode_is_in_charset("lbk",      mode) == true)
		{
			if (mode_check_arg_error(server, arg_index, toggle) == false)
				return ; // TODO error msg;
			arg = first_arg[arg_index];
			set_arg_modes(channel, mode, arg, toggle);
			arg_index++;
		}

		/* ................. MODE NOT FOUND ................. */
		else {
			err_msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
			send(user.getFd(), err_msg.c_str(), err_msg.length(), 0);
			return ;
		}
	}

	if (mode_is_in_charset("opsitnvmlbk", msg[1]) == true)
		channel->sendToAll(&user, "MODE", msg);

	/////////////////////// TODO delete
	if (Debug) __debug_modes(channel, "Before");
	/////////////////////// TODO delete
}


