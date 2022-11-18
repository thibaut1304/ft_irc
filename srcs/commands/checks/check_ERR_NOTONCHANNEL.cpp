/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOTONCHANNEL.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:53:11 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/09 17:35:20 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static bool check(Server *server, User user)
{
	BUFFER_           buffer  = server->get_allBuff();
	BUFFER_::iterator it      = buffer.begin();
	std::string       ch_name = *(it + 1);
	std::string       user_name = user.getNickname();

	//if (server->does_channel_exist(ch_name) == false) return NOT_OK_;
	Channel *channel = (server->getChannel(ch_name));
	if (channel->does_user_exist(user_name) == false) return NOT_OK_;
	return OK_;
}

bool check_ERR_NOTONCHANNEL(Server *server, User user)
{
	int destination = user.getFd();
	BUFFER_           buffer  = server->get_allBuff();
	BUFFER_::iterator it      = buffer.begin();
	std::string       ch_name = *(it + 1);
	std::string msg;

	if (user.get_is_operator() == true)
		return OK_;
	if (check(server, user) == NOT_OK_)
	{
		msg += ERR_NOTONCHANNEL(user.getNickname(), ch_name);
		send(destination, msg.c_str(), msg.length(), 0);;
		return NOT_OK_;
	}
	return OK_;
}
