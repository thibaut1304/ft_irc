/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:37:17 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/07 15:39:37 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// TODO WIP
// TODO WIP
// TODO WIP
// TODO WIP

/* ========================================================================== */
/* ------------------------------- USER MODES ------------------------------- */
/* ========================================================================== */

//static void exec_user_modes(User user, std::string modes)
//{
//bool toggle = true;
//(void)user;
//(void)modes;
//(void)toggle;

//if (modes[0] == '-')
//{
//toggle = false;
//modes = &modes[1];
//}
//}

/* ========================================================================== */
/* ----------------------------- CHANNEL MODES ------------------------------ */
/* ========================================================================== */

static bool is_channel_name(std::string str) {	return (str[0] == '#'); }


/* ...................................................... */
/* ...................... SETTERS ....................... */
/* ...................................................... */
static bool channel_mode_p(bool toggle, Channel * channel) { if (channel->get_is_private()          == toggle) return false; else return (channel->set_is_private          (toggle), true); };
static bool channel_mode_s(bool toggle, Channel * channel) { if (channel->get_is_secret()           == toggle) return false; else return (channel->set_is_secret           (toggle), true); };
static bool channel_mode_i(bool toggle, Channel * channel) { if (channel->get_is_invite_only()      == toggle) return false; else return (channel->set_is_invite_only      (toggle), true); };
static bool channel_mode_t(bool toggle, Channel * channel) { if (channel->get_is_topic_unlocked()   == toggle) return false; else return (channel->set_is_topic_unlocked   (toggle), true); };
static bool channel_mode_m(bool toggle, Channel * channel) { if (channel->get_is_moderated()        == toggle) return false; else return (channel->set_is_moderated        (toggle), true); };
static bool channel_mode_v(bool toggle, Channel * channel) { if (channel->get_mute_non_moderators() == toggle) return false; else return (channel->set_mute_non_moderators (toggle), true); };

static bool channel_mode_n(bool toggle, Channel * channel) {
	if (channel->get_is_accepting_messages_from_outside_client() == toggle)	return false;
	else return (channel->set_is_accepting_messages_from_outside_client (toggle), true);
};

/* ...................................................... */
/* ..................... EXEC MODES ..................... */
/* ...................................................... */
static void set_modes(User user, char mode, bool toggle, Channel * channel)
{
	bool modified = false;
	std::string msg;

	//if (mode == 'o') channel_mode_o(toggle, channel);
	if (mode == 'p') modified = channel_mode_p(toggle, channel);
	if (mode == 's') modified = channel_mode_s(toggle, channel);
	if (mode == 'i') modified = channel_mode_i(toggle, channel);
	if (mode == 't') modified = channel_mode_t(toggle, channel);
	if (mode == 'm') modified = channel_mode_m(toggle, channel);
	if (mode == 'v') modified = channel_mode_v(toggle, channel);
	if (mode == 'n') modified = channel_mode_n(toggle, channel);

	//if (mode == 'l')
	//if (mode == 'b')
	//if (mode == 'k')

	if (modified)
	{
		if (toggle == true)  msg = "+";
		if (toggle == false) msg = "-";
		msg += mode;
		channel->sendToAll(&user, "MODE", msg);
	}
}

static void parse_modes(User user, char mode, bool toggle, Channel * channel)
{
	std::string msg;
	std::string charset = "opsitnmlbvk";
	for (size_t j = 0; j < charset.length(); j++)
		if (mode == charset[j])
		{
			set_modes(user, mode, toggle, channel);
			return ;
		}
	msg = ERR_UNKNOWNMODE(user.getNickname(), mode);
	send(user.getFd(), msg.c_str(), msg.length(), 0);
	return ;
}

static void exec_channel_modes(User user, std::string modes, Channel * channel)
{
	bool toggle = true;
	if (modes[0] == '-' || modes [0] == '+')
	{
		if (modes[0] == '-')
			toggle = false;
		modes = &modes[1];
	}
	for (size_t i = 0; i < modes.length(); i++)
		parse_modes(user, modes[i], toggle, channel);
}

/* ========================================================================== */
/* ---------------------------------- MAIN ---------------------------------- */
/* ========================================================================== */

void   mode(Server               *server, User  user)
{
	(void)user;
	if (check_ERR_NEEDMOREPARAMS (server, user) == NOT_OK_) return ;
	if (check_ERR_NOTREGISTERED  (server, user) == NOT_OK_) return ;
	if (check_ERR_NOSUCHCHANNEL  (server, user) == NOT_OK_) return ;
	if (check_ERR_NOTONCHANNEL   (server, user) == NOT_OK_) return ;
	//if (check_ERR_NOSUCHNICK     (server, user)   == NOT_OK_) return ; // TODO
	//if (check_ERR_CHANOPRIVSNEEDED (server, user)   == NOT_OK_) return ; // TODO
	//if (check_ERR_KEYSET (server, user) == NOT_OK_) return ; // TODO

	BUFFER_           buffer          = server->_allBuff;
	BUFFER_::iterator it              = buffer.begin();

	std::string       command         = it[0];
	std::string       channel_or_user = it[1];
	std::string       modes           = it[2];

	if (is_channel_name(channel_or_user) == true)
	{
		Channel *channel = server->getChannel(channel_or_user);
		exec_channel_modes(user, modes, channel);
	}
	else
	{
		std::cout << "--------------- USER MODES WIP -------------------" << std::endl;
		//exec_user_modes(user, modes);
	}
}


/* ========================================================================== */
/* ---------------------------------- INFO ---------------------------------- */
/* ========================================================================== */

// 4.2.3 Mode message
//
//       Command: MODE
//
//    The MODE command is a dual-purpose command in IRC.  It allows both
//    usernames and channels to have their mode changed.  The rationale for
//    this choice is that one day nicknames will be obsolete and the
//    equivalent property will be the channel.
//
//    When parsing MODE messages, it is recommended that the entire message
//    be parsed first and then the changes which resulted then passed on.
//
// 4.2.3.1 Channel modes
//
//    Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
//                [<ban mask>]
//
//    The MODE command is provided so that channel operators may change the
//    characteristics of `their' channel.  It is also required that servers
//    be able to change channel modes so that channel operators may be
//    created.
//
//    The various modes available for channels are as follows:
//
//            o - give/take channel operator privileges;
//            p - private channel flag;
//            s - secret channel flag;
//            i - invite-only channel flag;
//            t - topic settable by channel operator only flag;
//            n - no messages to channel from clients on the outside;
//            m - moderated channel;
//            l - set the user limit to channel;
//            b - set a ban mask to keep users out;
//            v - give/take the ability to speak on a moderated channel;
//            k - set a channel key (password).
//
//    When using the 'o' and 'b' options, a restriction on a total of three
//    per mode command has been imposed.  That is, any combination of 'o'
//    and
//
// 4.2.3.2 User modes
//
//    Parameters: <nickname> {[+|-]|i|w|s|o}
//
//    The user MODEs are typically changes which affect either how the
//    client is seen by others or what 'extra' messages the client is sent.
//    A user MODE command may only be accepted if both the sender of the
//    message and the nickname given as a parameter are both the same.
//
//    The available modes are as follows:
//
//            i - marks a users as invisible;
//            s - marks a user for receipt of server notices;
//            w - user receives wallops;
//            o - operator flag.
//
//    Additional modes may be available later on.
//
//    If a user attempts to make themselves an operator using the "+o"
//    flag, the attempt should be ignored.  There is no restriction,
//    however, on anyone `deopping' themselves (using "-o").  Numeric
//    Replies:
//
//            ERR_NEEDMOREPARAMS              RPL_CHANNELMODEIS
//            ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK
//            ERR_NOTONCHANNEL                ERR_KEYSET
//            RPL_BANLIST                     RPL_ENDOFBANLIST
//            ERR_UNKNOWNMODE                 ERR_NOSUCHCHANNEL
//
//            ERR_USERSDONTMATCH              RPL_UMODEIS
//            ERR_UMODEUNKNOWNFLAG
//
//    Examples:
//
//            Use of Channel Modes:
//
// MODE #Finnish +im               ; Makes #Finnish channel moderated and
//                                 'invite-only'.
//
// MODE #Finnish +o Kilroy         ; Gives 'chanop' privileges to Kilroy on
//
//                                 channel #Finnish.
//
// MODE #Finnish +v Wiz            ; Allow WiZ to speak on #Finnish.
//
// MODE #Fins -s                   ; Removes 'secret' flag from channel
//                                 #Fins.
//
// MODE #42 +k oulu                ; Set the channel key to "oulu".
//
// MODE #eu-opers +l 10            ; Set the limit for the number of users
//                                 on channel to 10.
//
// MODE &oulu +b                   ; list ban masks set for channel.
//
// MODE &oulu +b *!*@*             ; prevent all users from joining.
//
// MODE &oulu +b *!*@*.edu         ; prevent any user from a hostname
//                                 matching *.edu from joining.
//
//         Use of user Modes:
//
// :MODE WiZ -w                    ; turns reception of WALLOPS messages
//                                 off for WiZ.
//
// :Angel MODE Angel +i            ; Message from Angel to make themselves
//                                 invisible.
//
// MODE WiZ -o                     ; WiZ 'deopping' (removing operator
//                                 status).  The plain reverse of this
//                                 command ("MODE WiZ +o") must not be
//                                 allowed from users since would bypass
//                                 the OPER command.
