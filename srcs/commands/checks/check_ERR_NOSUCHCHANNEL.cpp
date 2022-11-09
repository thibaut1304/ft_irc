/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOSUCHCHANNEL.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:19:24 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/07 16:23:17 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NOSUCHCHANNEL(Server * server, User user)
{
	int                  destination = user.getFd();
	BUFFER_           buffer      = server->_allBuff;
	BUFFER_::iterator it          = buffer.begin();
	std::string nick              = user.getNickname();
	std::string          msg;
	std::string channel_name ;

	if ((buffer.size()) > 1)
	{
		channel_name =  *(++it);
		if (channel_name[0] == '#')
		{
			channel_name = &channel_name[1];
			if (server->does_channel_exist(channel_name) == false)
			{
				msg = ERR_NOSUCHCHANNEL(nick, channel_name);
				send(destination, msg.c_str(), msg.length(), 0);
				return NOT_OK_;
			}
		}
	}
	return OK_;
}
