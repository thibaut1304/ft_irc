/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:30:19 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 19:40:11 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	notice(Server *serv, User user) {
	std::cout << "CMD NOTICE A COMPLETER"  << std::endl;
	if (serv->_allBuff.size() <= 2) { // Si pas le bon nombre de parametre
		std::string nick;
		if (user.getValidUser() == false) nick = "*"; else nick = user.getNickname();
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), nick);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->_allBuff.size() > 2 && user.getValidUser() == false) { // Si bon nombre de parametre mais user pas register
		std::string msg = NAME + ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
}