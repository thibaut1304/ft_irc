/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   john.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:24:09 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/07 22:57:53 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void john(Server *server, User user)
{
	int                  destination = user.getFd();
	VEC_<STR_>           buffer      = server->_allBuff;
	VEC_<STR_>::iterator it          = buffer.begin();
	std::string          msg;

	(void)user;
	(void)destination;
	(void)it;
	(void)msg;
	(void)buffer;

	if (server->does_channel_exist("test") == false)
		server->addChannel("test", user.getFd());
	if (server->does_channel_exist("test") == false)
		server->addChannel("test", user.getFd());
	if (server->does_channel_exist("test2") == false)
		server->addChannel("test2", user.getFd());
	if (server->does_channel_exist("test3") == false)
		server->addChannel("test3", user.getFd());
	if (server->does_channel_exist("test3") == true)
		server->join_channel("test3", user.getFd());

	server->printAllChannels();
	server->printAllUsers_from_channel("test");
	server->printAllUsers_from_channel("test2");
	server->printAllUsers_from_channel("test3");
}
