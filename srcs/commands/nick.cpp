/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 16:47:37 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

// bool	search_all_user(Server *serv) {
// 	std::map
// 	return (false);
// }

void	nick(Server *serv, User user) {
	// if (serv->_allBuff.size() == 2 && search_all_user(serv)) {
	// 	std::string msg = 
	// }
	if (serv->_allBuff.size() == 1) {
		std::string msg = NAME + " 431 * " + print_cmd(serv->_allBuff) + ERR_NONICKNAMEGIVEN;	
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->_allBuff.size() > 2) {
		std::string msg = NAME + " 432 * " + ERR_ERRONEUSNICKNAME(print_allBuff(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->_users[user.getFd()].setNickname(print_allBuff(serv->_allBuff));
	}
}