/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:20:10 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/15 18:23:14 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	pong(Server *serv, User user) {
	if (serv->_allBuff.size() == 1 && user.getValidUser() == false) {
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), std::string("*"));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->_allBuff.size() == 1 && user.getValidUser() == true) {
		std::string msg = NAME + ERR_NEEDMOREPARAMS(user.getNickname(), print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->_allBuff.size() > 1 && user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
}