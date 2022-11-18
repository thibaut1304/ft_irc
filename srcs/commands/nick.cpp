/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/18 15:49:41 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool	search_all_user(Server *serv, User user) {
	std::map<int, User>::iterator it_user = serv->getUsers().begin();
	std::map<int, User>::iterator ite_user = serv->getUsers().end();
	std::vector<std::string>::iterator it_buff = ++serv->get_buff().begin();

	for (; it_user != ite_user;it_user++) {
		if (it_user->second.getNickname() == *it_buff && it_user->second.getFd() != user.getFd())
			return (true);
	}
	return (false);
}

void	nick(Server *serv, User user) {
	if (serv->get_buff().size() == 2 && search_all_user(serv, user)) {
		std::string msg = NAME + ERR_NICKNAMEINUSE(print_allBuff(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_buff().size() == 1) {
		std::string msg = NAME + ERR_NONICKNAMEGIVEN(print_cmd(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_buff().size() > 2) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(std::string("*"), print_allBuff(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (isdigit(print_allBuff(serv->get_buff()).c_str()[0]) || (findCharParsing(print_allBuff(serv->get_buff())) && user.getValidUser() == false)) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(std::string("*"), print_allBuff(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (isdigit(print_allBuff(serv->get_buff()).c_str()[0]) || (findCharParsing(print_allBuff(serv->get_buff())) && user.getValidUser() == true)) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(user.getNickname(), print_allBuff(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (!serv->getUsers()[user.getFd()].getNickname().empty() \
		&& serv->getUsers()[user.getFd()].getValidUser() == true	\
		&& user.getNickname().compare(print_allBuff(serv->get_buff())) != 0 ) {
		std::string msg = ":" + serv->getUsers()[user.getFd()].getNickname() + "!" \
		+ serv->getUsers()[user.getFd()].getUsername() + "@" + serv->getUsers()[user.getFd()].getIp() \
		+ " " + print_cmd(serv->get_buff()) + " :" + print_allBuff(serv->get_buff()) + "\r\n";
		serv->getUsers()[user.getFd()].setNickname(print_allBuff(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->getUsers()[user.getFd()].setNickname(print_allBuff(serv->get_buff()));
	}
}
