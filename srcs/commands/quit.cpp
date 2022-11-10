/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:00:09 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/10 16:17:29 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>



// static void	print_chanel_of_user(std::vector<std::string> tmp) {
// 	std::vector<std::string>::iterator it = tmp.begin();
// 	for (;it != tmp.end();it++) {
// 		std::cout << _CYAN << *it << _NC << std::endl;
// 	}
// }

static void	printChanOfUser(Server *serv, User user, std::vector<std::string> & tmp) {
	std::map<std::string, Channel * >::iterator it = serv->_channels.begin();
	for (;it != serv->_channels.end();it++) {
		std::map<std::string, User * > tabUser = it->second->getUsers();

		std::map<std::string, User * >::iterator it_user = tabUser.begin();
		for (; it_user != tabUser.end();it_user++) {
			if (it_user->first.compare(user.getNickname()) == 0) {
				tmp.push_back(it->first);
			}
		}
	}
	// print_chanel_of_user(tmp);
}

void	printOtherClient(std::map<std::string, int> otherClient, User user, std::vector<std::string> buff) {
	std::map<std::string, int>::iterator it = otherClient.begin();

// :a!1@172.17.0.1 QUIT :Quit: bye   	--> avec msg
// :a!1@172.17.0.1 QUIT :Client exited 	--> sans msg
	std::string msgQuit;
	if (buff.size() > 1)
		msgQuit = "Quit: " + print_allBuff(buff) + "\r\n";
	else
		msgQuit = "Client exited \r\n";
	for ( ; it != otherClient.end() ; it++) {
		std::string msg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getIp() + " QUIT :" + msgQuit;
		send(it->second, msg.c_str(), msg.length(), 0);
	}
}

static void sendOtherClient(Server *serv, User user, std::vector<std::string> tmp, std::map<std::string, int> & otherClient) {
	std::vector<std::string>::iterator it_tmp = tmp.begin();

	for ( ; it_tmp != tmp.end() ; it_tmp++) {
		std::map<std::string, Channel * >::iterator it = serv->_channels.find(*it_tmp);
		std::map<std::string, User * > tabUser = it->second->getUsers();

		std::map<std::string, User * >::iterator it_user = tabUser.begin();
		for (; it_user != tabUser.end();it_user++) {
			if (it_user->first.compare(user.getNickname()) != 0)
				otherClient[it_user->first] = it_user->second->getFd();
		}
	}
	printOtherClient(otherClient, user, serv->_allBuff);
}

void	quit(Server *serv, User user) {
	std::vector<std::string> tmp;
	printChanOfUser(serv, user, tmp);

	std::map<std::string, int> otherClient;
	sendOtherClient(serv, user, tmp, otherClient);

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
