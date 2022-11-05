/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 01:43:34 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/05 15:04:50 by thhusser         ###   ########.fr       */
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

static void		search_clientRPL(std::vector<std::string> Client, std::map<const int, User> user, std::vector<std::string> allBuff, User user_send) {
	std::string cmd = *(allBuff.begin());
	allBuff.erase(allBuff.begin());
	std::map<std::string, int> tmp;
	for (std::map<const int, User>::iterator it_u = user.begin() ; it_u != user.end(); it_u++) {
		tmp[it_u->second.getNickname()] = it_u->first;
	}
	for (std::vector<std::string>::iterator it_find = Client.begin() ; it_find != Client.end() ; it_find++) {
		std::map<std::string, int>::iterator it_tmp = tmp.find(*it_find);
		if (it_tmp == tmp.end()) {
			std::string msg = ERR_NOSUCHNICK(user_send.getNickname(), *it_find);
			send(user_send.getFd(), msg.c_str(), msg.length(), 0);
		}
		else if (it_tmp != tmp.end()) {
				std::string msg_client = std::string(":") + user_send.getNickname() + "!" + user_send.getUsername() \
				+ "@" + user_send.getIp() + " " + cmd + " " + *it_find + " :" + print_allBuff(allBuff) + std::string("\r\n");
				send(it_tmp->second, msg_client.c_str(), msg_client.length(), 0);
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
		std::vector<std::string> client;
		std::vector<std::string>::iterator it_buff = ++serv->_allBuff.begin();
		splitCmdClient(client, *it_buff);
		search_clientRPL(client, serv->_users, serv->_allBuff, user);
	}
}
