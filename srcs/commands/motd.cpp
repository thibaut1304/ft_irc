/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:21:47 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 18:52:43 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	motd(Server *serv, User user) {
	if (user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		std::cout << print_cmd(serv->_allBuff);
	}
	else if (user.getValidUser() == true && serv->_allBuff.size() > 1) {
		return ; 
	}
	else {
		std::string msg = RPL_MOTDSTART(user.getNickname());
		msg += RPL_MOTD(user.getNickname(), std::string("+---------------------------------------------------+"));
		msg += RPL_MOTD(user.getNickname(), std::string("|                    z I R C o n                    |"));
		msg += RPL_MOTD(user.getNickname(), std::string("+---------------------------------------------------+"));
		msg += RPL_ENDOFMOTD(user.getNickname());
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
}