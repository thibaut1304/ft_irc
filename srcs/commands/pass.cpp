/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:58:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 23:39:40 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	pass(Server *serv, User user) {
	if (serv->get_buff().size() == 1) {
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->get_buff()), std::string("*"));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == true) {
		std::string msg = NAME + ERR_ALREADYREGISTRED(user.getNickname());
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	} else if (serv->getPasswd().compare(print_allBuff(serv->get_buff()))) {
		std::string msg = ERR_PASSWDMISMATCH(user.getNickname());
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		serv->getUsers()[user.getFd()].setPASS(print_allBuff(serv->get_buff()));
	}
	return ;
}
