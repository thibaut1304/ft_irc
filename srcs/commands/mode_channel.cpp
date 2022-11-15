/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 06:08:41 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/15 19:16:35 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"
#include "Mode.hpp"

/* ========================================================================== */
/* ------------------------------- MODE QUERY ------------------------------- */
/* ========================================================================== */
static bool mode_channel_log(Channel * channel, User user, size_t buffer_size)
{
	if (buffer_size != 2)
		return false;

	std::stringstream user_limit_ss;

	if (channel->get_user_limit() > 0)
		user_limit_ss << channel->get_user_limit();

	std::string msg = "";

	msg += ":" + NAME_V;
	msg += " 324 ";
	msg += user.getNickname() + " " ;
	msg += channel->getName();
	msg += " :+";

	msg += channel->get_is_invite_only()                            ? 'i' : char(0);
	msg += channel->get_channel_key().size() > 0                    ? 'k' : char(0);
	msg += channel->get_user_limit()         > 0                    ? 'l' : char(0);
	msg += channel->get_is_moderated()                              ? 'm' : char(0);
	msg += channel->get_is_accepting_messages_from_outside_client() ? 'n' : char(0);
	msg += channel->get_is_private()                                ? 'p' : char(0);
	msg += channel->get_is_secret()                                 ? 's' : char(0);
	msg += channel->get_is_topic_unlocked()                         ? 't' : char(0);
	msg += channel->get_mute_non_moderators()                       ? 'v' : char(0);

	msg += channel->get_channel_key().size() > 0                    ? " :" +channel->get_channel_key() : "";
	msg += channel->get_user_limit()         > 0                    ? " :" + user_limit_ss.str() : "";

	msg += "\r\n";

	send(user.getFd(), msg.c_str(), msg.length(), 0);
	return true;
}


/* ========================================================================== */
/* -------------------------------- BOOLEANS -------------------------------- */
/* ========================================================================== */

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
/* .................BOOL EXEC MODES ..................... */
/* ...................................................... */
static char set_bool_modes(Channel * channel, char mode, bool toggle)
{
	bool modified = false;

	if (mode == 'i') modified = channel_mode_i(toggle, channel);
	if (mode == 'm') modified = channel_mode_m(toggle, channel);
	if (mode == 'n') modified = channel_mode_n(toggle, channel);
	//if (mode == 'o') channel_mode_o(toggle, channel); // TODO
	if (mode == 'p') modified = channel_mode_p(toggle, channel);
	if (mode == 's') modified = channel_mode_s(toggle, channel);
	if (mode == 't') modified = channel_mode_t(toggle, channel);
	if (mode == 'v') modified = channel_mode_v(toggle, channel);

	return modified ? mode : char(0);
}

/* ========================================================================== */
/* ------------------------------- ARGUMENTS -------------------------------- */
/* ========================================================================== */

/* ...................................................... */
/* .................... ARG SETTERS ..................... */
/* ...................................................... */
static bool channel_mode_b(std::string new_ban_mask, Channel * C_) { if (C_->does_ban_mask_exist(new_ban_mask)) return false; else return (C_->set_ban_mask    (new_ban_mask), true); }
static bool channel_mode_k(std::string new_key,      Channel * C_) { if (C_->get_channel_key() == new_key)      return false; else return (C_->set_channel_key (new_key),      true); }
static bool channel_mode_l(size_t      new_limit,    Channel * C_) { if (C_->get_user_limit()  == new_limit)    return false; else return (C_->set_user_limit  (new_limit),    true); }

/* ..................................................... */
/* .................. ARG EXEC MODES ................... */
/* ..................................................... */

static char set_arg_modes(Channel* channel, User user, char mode, std::string arg, bool toggle)
{
	bool        modified = false;
	std::string num_arg  = toggle ? arg : "0";

	std::string msg;

	if (mode == 'b') modified = channel_mode_b(arg, channel);
	if (mode == 'l') modified = channel_mode_l(mode_str_to_num(num_arg), channel);
	if (mode == 'k')
	{
		if (mode_is_missing_password(channel, user, arg)         == true) return char(0);
		if (mode_is_invalid_password(channel, user, arg, toggle) == true) return char(0);
		if      (toggle == true  && channel->get_channel_key().size() == 0) modified = channel_mode_k(arg, channel);
		else if (toggle == false && channel->get_channel_key() == arg)      modified = channel_mode_k("",  channel);
	}
	return modified ? mode : char(0);
}


/* ========================================================================== */
/* ---------------------------------- MAIN ---------------------------------- */
/* ========================================================================== */

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

	// NOTE code stops here if buffer.size() == 2
	// This prints all channel modes that are set to true
	if (mode_channel_log(channel, user, buffer.size()) == true) return;

	/////////////////////// TODO delete
	if (Debug) __debug_modes(channel, "Before");
	/////////////////////// TODO delete

	for (size_t mode_index = 0; mode_index < modes.length(); mode_index++)
	{
		mode = modes[mode_index];

		/* BOOL MODES ............... */
		/* .......................... */
		if (mode_is_in_charset("opsitnvm", mode) == true)
			msg += set_bool_modes(channel, mode, toggle);

		/* DATA MODES ............... */
		/* .......................... */
		else if (mode_is_in_charset("lbk", mode) == true)
		{
			arg = first_arg == buffer.end() ? "" : first_arg[arg_index];
			msg += set_arg_modes(channel, user, mode, arg, toggle);
			arg_index++;
		}

		/* MODE NOT FOUND ........... */
		/* .......................... */
		else {
			err_msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
			send(user.getFd(), err_msg.c_str(), err_msg.length(), 0);
			return ;
		}
	}

	if (mode_is_in_charset("opsitnvmlbk", msg[1]) == true)
		channel->sendToAll(&user, "MODE", msg);

	/////////////////////// TODO delete
	if (Debug) __debug_modes(channel, "After");
	/////////////////////// TODO delete
}


