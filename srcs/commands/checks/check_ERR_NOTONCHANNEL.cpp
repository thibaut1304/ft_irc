/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOTONCHANNEL.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:53:11 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/05 17:53:40 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO
// TODO

bool check_ERR_NOTONCHANNEL(Server *server, User user)
{
	(void)user;
	VEC_<STR_>           buffer      = server->_allBuff;
	std::map<std::string, Channel>::iterator channel_it ;
	VEC_<STR_>::iterator it          = buffer.begin();
	STR_ 				 channel = *it;

	channel_it = server->_channels.find(channel);
	if (channel_it == server->_channels.end())
	{
		std::cout << "notok" << std::endl;
		return NOT_OK_;
	}
		std::cout << "ok" << std::endl;
	return OK_;

}
