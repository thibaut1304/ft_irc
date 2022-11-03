/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:00:09 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/03 22:57:56 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	quit(Server *serv, User user) {
	std::cout << "Quand un user quit faut envoyer un msg aux personne present dans le meme channel\n pour informer que le user quit" << std::endl;
	std::string msg;
	if (user.getValidUser() == false && serv->_allBuff.size() == 1) {
		msg = CLIENT_EXIT(NAME_V, user.getIp(), "Client exited");
	}
	else if (user.getValidUser() == false) {
		std::string text = "Quit: " + print_allBuff(serv->_allBuff);
		msg = CLIENT_EXIT(NAME_V, user.getIp(), text);
	}
	else if (user.getValidUser() == true && serv->_allBuff.size() == 1) {
		msg = CLIENT_EXIT(user.getUsername(), user.getIp(), "Client exited");
	}
	else {
		std::string text = "Quit: " + print_allBuff(serv->_allBuff);
		msg = CLIENT_EXIT(user.getUsername(), user.getIp(), text);
	}
	send(user.getFd(), msg.c_str(), msg.length(), 0);
	serv->_users[user.getFd()].setIsKill(true);
	serv->killUserClient(user.getFd());
}