/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.check_ERR_NONICKNAMEGIVEN.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 00:56:24 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/08 01:00:29 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "connectionReplies.hpp"

bool check_ERR_NONICKNAMEGIVEN(Server * server, User user)
{
	int                  destination = user.getFd();
	BUFFER_           buffer      = server->get_allBuff();
	BUFFER_::iterator it          = buffer.begin();
	std::string msg;

	if (buffer.size() == 1)
	{
		msg = ERR_NONICKNAMEGIVEN(*it);
		send(destination, msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}

