/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 06:10:02 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/18 11:24:17 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Mode.hpp"

/* ========================================================================== */
/* --------------------------------- UTILS ---------------------------------- */
/* ========================================================================== */

void __debug_modes(Channel *channel, std::string str)
{
	if (Debug) {
		std::cout << "============================================" << std::endl;
		std::cout << str << std::endl;
		std::cout << "chan key              :"<< channel->get_channel_key()                               << std::endl;

		//std::vector<std::string> cpy = channel->get_ban_mask();
		//std::vector<std::string>::iterator it = cpy.begin();
		//std::vector<std::string>::iterator ite = cpy.end();
		//int i = 1;
		//for (; it != ite; it++, i++)
			//std::cout << "ban mask : " << i << "            :"<< *it<< std::endl;

		std::cout << "accept outside client :"<< channel->get_is_accepting_messages_from_outside_client() << std::endl;
		std::cout << "inv only              :"<< channel->get_is_invite_only()                            << std::endl;
		std::cout << "moderated             :"<< channel->get_is_moderated()                              << std::endl;
		std::cout << "private               :"<< channel->get_is_private()                                << std::endl;
		std::cout << "secret                :"<< channel->get_is_secret()                                 << std::endl;
		std::cout << "unlocked topic        :"<< channel->get_is_topic_unlocked()                         << std::endl;
		std::cout << "mute non operators    :"<< channel->get_mute_non_moderators()                       << std::endl;
		std::cout << "user limit            :"<< channel->get_user_limit()                                << std::endl;
		std::cout << "============================================" << std::endl;
	}
}

//static bool is_channel_name(std::string str) {	return (str[0] == '#'); }
size_t mode_str_to_num(std::string arg)
{
	size_t limit;
	std::stringstream ss;
	ss << arg;
	ss >> limit;
	return limit;
}

bool mode_is_in_charset(std::string charset, char c)
{
	for (size_t j = 0; j < charset.length(); j++)
		if (c == charset[j])
			return true;
	return false;
}

bool mode_get_sign(std::string modes)
{
	if (modes[0] == '-' || modes[0] == '+')
		return ((modes[0] == '-') ? false : true) ;
	return true;
}

std::string mode_trim_sign (std::string modes)
{
	return ( modes[0] == '-' || modes[0] == '+') ? &modes[1] : modes;
}

bool mode_check_arg_error(Server *server, int arg_index, bool toggle)
{
	BUFFER_           buffer          = server->_allBuff;
	BUFFER_::iterator it              = buffer.begin();
	BUFFER_::iterator first_arg = it + 3;
	int arg_count = 0;
	(void)toggle;

	while (first_arg + arg_count < buffer.end())
		arg_count++;

	if (arg_count < arg_index || (arg_count == 0))
	{
		if (Debug)
			std::cout << "ERROR" << std::endl;
		return NOT_OK_; // TODO error
	}
	return OK_;
}

bool mode_is_missing_password(Channel * channel, User user, std::string password)
{
	std::string msg;
	if (password.size() == 0)
	{
		msg += ":" + NAME_V;
		msg += " 696 ";
		msg += user.getNickname() + " ";
		msg += channel->getName() + " ";
		msg += "k * :You must specify a parameter for the key mode. Syntax: <key>.";
		msg += "\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return true;
	}
	return false;
}

bool mode_is_invalid_password(Channel * channel, User user, std::string password, bool toggle)
{
	// NOTE only gets triggered with removal of key (-)
	std::string msg;

	if (
			toggle == false &&
			channel->get_channel_key() != password &&
			channel->get_channel_key().size() > 0
	   )
	{
		msg += ":" + NAME_V;
		msg += " 467 ";
		msg += user.getNickname() + " " ;
		msg += channel->getName();
		msg += " :Channel key already set";
		msg += "\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return true;
	}
	return false;
}






