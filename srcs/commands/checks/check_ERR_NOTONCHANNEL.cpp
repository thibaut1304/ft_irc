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
#include "Channel.hpp"

bool check_ERR_NOTONCHANNEL(Server *server, User user)
{
	(void)user;
	// int                  destination = user.getFd();
	VEC_<STR_> buffer = server->_allBuff;
	std::map<std::string, Channel *>::iterator channel_it;
	VEC_<STR_>::iterator it = buffer.begin();
	STR_ channel = *it;
	// STR_                 msg;

	channel_it = server->_channels.find(channel);
	if (channel_it == server->_channels.end())
	{
		std::cout << "notok" << std::endl;
		return NOT_OK_;
	}
	std::cout << "ok" << std::endl;
	return OK_;
}
