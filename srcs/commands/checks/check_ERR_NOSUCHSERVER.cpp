/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOSUCH_SERVER.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:33:59 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 16:35:50 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NOSUCHSERVER(Server *server, User user)
{
	int               destination = user.getFd();
	BUFFER_           buffer      = server->_allBuff;
	BUFFER_::iterator it          = buffer.begin();
	std::string       msg;

	if (buffer.size() > 1)
	{
		if (*(++it) != NAME_V)
		{
			msg =  ERR_NOSUCHSERVER(*it);
			send(destination, msg.c_str(), msg.length(), 0);
			return NOT_OK_;
		}
	}
	return OK_;
}
