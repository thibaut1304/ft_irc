/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:13:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/15 18:18:47 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::string secondParam(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	++it;
	return (*it);
}

static std::string thirdParam(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	(++(++it));	
	return (*it);	
}


void	ping(Server *serv, User user) {
	if (serv->get_allBuff().size() == 1 && user.getValidUser() == false) {
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->get_allBuff()), std::string("*"));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}else if (serv->get_allBuff().size() == 1 && user.getValidUser() == true) {
		std::string msg = NAME + ERR_NEEDMOREPARAMS(user.getNickname(), print_cmd(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_allBuff().size() > 1 && user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_allBuff().size() == 2) {
		std::string msg = NAME + " PONG " + NAME_V + " :" + print_allBuff(serv->get_allBuff()) + "\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		std::string msg = NAME + " PONG " + thirdParam(serv->get_allBuff()) + " :" + secondParam(serv->get_allBuff()) + "\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
}
