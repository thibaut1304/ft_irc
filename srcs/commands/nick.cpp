/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/02 16:37:49 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool	search_all_user(Server *serv, User user) {
	std::map<int, User>::iterator it_user = serv->_users.begin();
	std::vector<std::string>::iterator it_buff = ++serv->_allBuff.begin();
	
	for (; it_user != serv->_users.end();it_user++) {
		if (it_user->second.getNickname() == *it_buff && it_user->second.getFd() != user.getFd())
			return (true);
	}
	return (false);
}

void	nick(Server *serv, User user) {
	
	std::cout << _CYAN << "CMD NICK" << _NC << std::endl;
	
	if (serv->_allBuff.size() == 2 && search_all_user(serv, user)) {
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
	else if (!serv->_users[user.getFd()].getNickname().empty() \
		&& serv->_users[user.getFd()].getValidUser() == true	\
		&& user.getNickname().compare(print_allBuff(serv->_allBuff)) != 0) {
		std::string msg = ":" + serv->_users[user.getFd()].getNickname() + "!" \
		+ serv->_users[user.getFd()].getUsername() + "@" + serv->_users[user.getFd()].getIp() \
		+ " " + print_cmd(serv->_allBuff) + " :" + print_allBuff(serv->_allBuff) + "\r\n";
		serv->_users[user.getFd()].setNickname(print_allBuff(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->_users[user.getFd()].setNickname(print_allBuff(serv->_allBuff));
	}
}