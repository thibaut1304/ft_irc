/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.check_ERR_NOSUCHNICK.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 01:02:41 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/08 01:04:57 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NOSUCHNICK(Server * server, User user)
{
	int                  destination = user.getFd();
	VEC_<STR_>           buffer      = server->_allBuff;
	VEC_<STR_>::iterator it          = buffer.begin();
	std::string          nick        = it[1];
	std::string msg;

	Server::map_users users = server->get_users();
	Server::map_users::iterator users_it = users.begin();
	Server::map_users::iterator users_ite = users.end();

	while (users_it != users_ite)
	{
		if (nick == users_it->second.getNickname())
			return OK_;
		users_it++;
	}
	msg += ERR_NOSUCHNICK(user.getNickname(), nick );
	send(destination, msg.c_str(), msg.length(),0);
	return NOT_OK_;

}
