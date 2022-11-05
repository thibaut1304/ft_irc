/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 01:43:34 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/05 03:37:26 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

static void	splitCmdClient(std::vector<std::string> & sCmd, std::string cmd) {

	size_t					pos = 0;
	std::string				delimiter = ",";
	std::string::iterator	it;

	while ((pos = cmd.find_first_of(delimiter)) != std::string::npos)
	{
		sCmd.push_back(cmd.substr(0, pos));
		for (it = cmd.begin() + pos; it != cmd.end() && delimiter.find(*it) != std::string::npos; it++)
			pos++;
		cmd.erase(0, pos);
	}
	int i = 0;
	while (std::isspace(cmd.c_str()[i])) i++;
	cmd.erase(0, i);
	if (!cmd.empty())
		sCmd.push_back(cmd.substr(0, pos));
}

static void		search_client(std::map<const int, std::string> & fdClient, std::vector<std::string> buff, std::map<const int, User> user) {
	std::vector<std::string>::iterator it = ++buff.begin();
	std::vector<std::string> client;

	splitCmdClient(client, *it);

	for (std::vector<std::string>::iterator it_client = client.begin() ; it_client != client.end() ; it_client++) {
		for (std::map<const int, User>::iterator it_user = user.begin(); it_user != user.end() ; it_user++) {
			if (it_user->second.getNickname().compare(*it_client) == 0)
				fdClient[it_user->first] = it_user->second.getNickname();
			else
				fdClient[it_user->first] = "@";  //--> bullshit a changer

		}
	}
}

static void 	sendErrorNick(std::map<const int, std::string> client, User user, Server *serv) {
	for (std::map<const int, std::string>::iterator it = client.begin() ; it != client.end() ; it++) {
		if (it->second.compare("@") == 0) {
			std::string msg = ERR_NOSUCHNICK(user.getNickname(), serv->_users[it->first].getNickname());
			send(user.getFd(), msg.c_str(), msg.length(), 0);
		}
	}
}

void	privmsg(Server *serv, User user) {
	if (serv->_allBuff.size() < 3) {
		std::string nick = "*";
		if (user.getValidUser() == true)
			nick = user.getNickname();
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), nick);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		std::map<const int, std::string> client;
		search_client(client, serv->_allBuff, serv->_users);
		std::string cmd = *(serv->_allBuff.begin());
		serv->_allBuff.erase(serv->_allBuff.begin());
		sendErrorNick(client, user, serv);
		for (std::map<const int, std::string>::iterator it = client.begin() ; it != client.end() ; it++) {
			if (it->second.compare("@") != 0) {
				std::string msg_client = std::string(":") + user.getNickname() + "!" + user.getUsername() \
				+ "@" + user.getIp() + " " + cmd + " " + it->second + " :" + print_allBuff(serv->_allBuff) + std::string("\r\n");
				send(it->first, msg_client.c_str(), msg_client.length(), 0);
			}
		}
	}
}
