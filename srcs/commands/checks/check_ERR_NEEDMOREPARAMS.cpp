/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NEEDMOREPARAMS.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:49:16 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/05 17:50:33 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NEEDMOREPARAMS(Server *server, User user)
{
	int                  destination = user.getFd();
	VEC_<STR_>           buffer      = server->_allBuff;
	VEC_<STR_>::iterator it          = buffer.begin();
	STR_                 username    = user.getNickname();
	STR_                 msg;

	username = (username == "") ? "*"  : username;

	if (buffer.size() < 2)
	{
		msg = NAME_V;
		msg += ERR_NEEDMOREPARAMS(*it, username);
		send(destination, msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}
