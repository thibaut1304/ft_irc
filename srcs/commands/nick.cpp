/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/05 01:15:21 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool	search_all_user(Server *serv, User user) {
	std::map<int, User>::iterator it_user = serv->get_users().begin();
	std::vector<std::string>::iterator it_buff = ++serv->get_allBuff().begin();

	for (; it_user != serv->get_users().end();it_user++) {
		if (it_user->second.getNickname() == *it_buff && it_user->second.getFd() != user.getFd())
			return (true);
	}
	return (false);
}

void	nick(Server *serv, User user) {
	if (serv->get_allBuff().size() == 2 && search_all_user(serv, user)) {
		std::string msg = NAME + ERR_NICKNAMEINUSE(print_allBuff(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_allBuff().size() == 1) {
		std::string msg = NAME + ERR_NONICKNAMEGIVEN(print_cmd(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->get_allBuff().size() > 2) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(std::string("*"), print_allBuff(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (isdigit(print_allBuff(serv->get_allBuff()).c_str()[0]) || (findCharParsing(print_allBuff(serv->get_allBuff())) && user.getValidUser() == false)) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(std::string("*"), print_allBuff(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (isdigit(print_allBuff(serv->get_allBuff()).c_str()[0]) || (findCharParsing(print_allBuff(serv->get_allBuff())) && user.getValidUser() == true)) {
		std::string msg = NAME + ERR_ERRONEUSNICKNAME(user.getNickname(), print_allBuff(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (!serv->get_users()[user.getFd()].getNickname().empty() \
		&& serv->get_users()[user.getFd()].getValidUser() == true	\
		&& user.getNickname().compare(print_allBuff(serv->get_allBuff())) != 0 ) {
		std::string msg = ":" + serv->get_users()[user.getFd()].getNickname() + "!" \
		+ serv->get_users()[user.getFd()].getUsername() + "@" + serv->get_users()[user.getFd()].getIp() \
		+ " " + print_cmd(serv->get_allBuff()) + " :" + print_allBuff(serv->get_allBuff()) + "\r\n";
		serv->get_users()[user.getFd()].setNickname(print_allBuff(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->get_users()[user.getFd()].setNickname(print_allBuff(serv->get_allBuff()));
	}
}
