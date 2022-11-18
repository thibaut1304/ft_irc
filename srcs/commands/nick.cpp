/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/18 15:40:00 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool	search_all_user(Server *serv, User user) {
	std::map<int, User>::iterator it_user = serv->_users.begin();
	std::vector<std::string>::iterator it_buff = ++serv->get_buff().begin();

	for (; it_user != serv->_users.end();it_user++) {
		if (it_user->second.getNickname() == *it_buff && it_user->second.getFd() != user.getFd())
			return (true);
	}
	return (false);
}

void	nick(Server *serv, User user) {
	if (serv->get_buff()().size() == 2 && search_all_user(serv, user)) {
		std::string msg = NAME + ERR_NICKNAMEINUSE(print_allBuff(serv->get_buff()()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_buff()().size() == 1) {
		std::string msg = NAME + ERR_NONICKNAMEGIVEN(print_cmd(serv->get_buff()()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_buff()().size() > 2) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(std::string("*"), print_allBuff(serv->get_buff()()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (isdigit(print_allBuff(serv->get_buff()()).c_str()[0]) || (findCharParsing(print_allBuf(serv->get_buff()ff()) && user.getValidUser() == false)) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(std::string("*"), print_allBuff(serv->get_buff()()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (isdigit(print_allBuff(serv->get_buff()()).c_str()[0]) || (findCharParsing(print_allBuf(serv->get_buff()ff()) && user.getValidUser() == true)) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(user.getNickname(), print_allBuff(serv->get_buff()()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (!serv->_users[user.getFd()].getNickname().empty() \
		&& serv->_users[user.getFd()].getValidUser() == true	\
		&& user.getNickname().compare(print_allBuff(serv->get_buff()())) != 0 ) {
		std::string msg = ":" + serv->_users[user.getFd()].getNickname() + "!" \
		+ serv->_users[user.getFd()].getUsername() + "@" + serv->_users[user.getFd()].getIp() \
		+ " " + print_cmd(serv->get_buff()()) + " :" + print_allBuf(serv->get_buff()) + "\r\n";
		serv->_users[user.getFd()].setNickname(print_allBuff(serv->get_buff()()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->_users[user.getFd()].setNickname(print_allBuff(serv->get_buff()()));
	}
}
