/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 17:17:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool	search_all_user(Server *serv) {
	std::map<int, User>::iterator it_user = serv->_users.begin();
	std::vector<std::string>::iterator it_buff = ++serv->_allBuff.begin();
	
	for (; it_user != serv->_users.end();it_user++) {
		if (it_user->second.getNickname() == *it_buff)
			return (true);
	}
	return (false);
}

void	nick(Server *serv, User user) {
	if (serv->_allBuff.size() == 2 && search_all_user(serv)) {
		std::string msg = NAME + ERR_NICKNAMEINUSE(print_allBuff(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	if (serv->_allBuff.size() == 1) {
		std::string msg = NAME + ERR_NONICKNAMEGIVEN(print_cmd(serv->_allBuff));	
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->_allBuff.size() > 2) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(print_allBuff(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->_users[user.getFd()].setNickname(print_allBuff(serv->_allBuff));
	}
}