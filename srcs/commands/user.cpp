/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:11:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 16:53:22 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

static std::string	findPoint(std::vector<std::string> & all) {
	std::vector<std::string>::iterator it = all.begin();
	int i = 0;
	for (; it != all.end();it++, i++) {
		if (it->c_str()[0] == ':') {
			break;
		}
	}
	std::string bis;
	std::vector<std::string>::iterator copy = it;
	for(; it != all.end(); it++) {
		bis += *it;
		if (it != --all.end())
			bis += " ";
	}
	std::string::iterator it_str = bis.begin();
	for (; it_str != bis.end();it_str++) {
		if (*it_str != ' ' && *it_str != '\t' && *it_str != ':')
			break;
	}
	if (it_str != bis.begin())
		bis.erase(bis.begin(), it_str);
	all.erase(copy, all.end());
	return (bis);
}

void	user(Server *serv, User user) {
	std::vector<std::string> all;
	
	std::cout << _CYAN << "CMD USER" << _NC << std::endl;
	
	
	std::string bis = findPoint(serv->_allBuff);
	if (bis.empty() || serv->_allBuff.size() != 4) {
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), std::string("*"));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == true) {
		std::string msg = NAME + ERR_ALREADYREGISTRED(user.getNickname());
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (findCharParsing(*(++serv->_allBuff.begin()))) {
		std::string msg = NAME + ERR_USERNAMENOTVALID(print_cmd(serv->_allBuff), std::string("*"));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		std::vector<std::string>::iterator it = ++serv->_allBuff.begin();
		serv->_users[user.getFd()].setUsername(*it++);
		serv->_users[user.getFd()].setHostname(*it++);
		serv->_users[user.getFd()].setHostname(*it);
		serv->_users[user.getFd()].setFullName(bis);
	}
}