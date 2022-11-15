/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:30:19 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/15 18:09:25 by thhusser         ###   ########.fr       */
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

static void	searchChannel(std::string nameChannel, Server *serv, User user, std::map<std::string, int> tmp) {
	bool user_in = false;
	std::vector<std::string> allBuff = serv->_allBuff;
	std::string cmd = *(allBuff.begin());
	allBuff.erase(allBuff.begin());

	if (serv->does_channel_exist(nameChannel)) {
		std::map<std::string, Channel *>::iterator it_chan= serv->_channels.find(nameChannel);
		std::cout << _GREEN << it_chan->first << _NC << std::endl;
		std::map<std::string, User * > tabUser = it_chan->second->getUsers();
		std::map<std::string, User * >::iterator it_user = tabUser.begin();
		for (; it_user != tabUser.end();it_user++) {
			if (it_user->first.compare(user.getNickname()) == 0)
				user_in = true;
		}
		if (!user_in) {
			std::string msg_user_out = ERR_CANNOTSENDTOCHAN(user.getNickname(), nameChannel);
			send(user.getFd(), msg_user_out.c_str(), msg_user_out.length(), 0);
		} else {
			for (it_user = tabUser.begin(); it_user != tabUser.end();it_user++) {
				std::map<std::string, int>::iterator it_tmp = tmp.find(it_user->first);
				if (it_tmp->first.compare(user.getNickname()) != 0){
					std::string msg_client = std::string(":") + user.getNickname() + "!" + user.getUsername() \
				+ "@" + user.getIp() + " " + cmd + " " + nameChannel + " :" + print_allBuff(allBuff) + std::string("\r\n");
					send(it_tmp->second, msg_client.c_str(), msg_client.length(), 0);
				}
			}
		}
	}
	else {
		std::string msg_error = ERR_NOSUCHCHANNEL_THH(nameChannel, user.getNickname());
		send(user.getFd(), msg_error.c_str(), msg_error.length(), 0);
	}
}

static void		search_clientRPL(std::vector<std::string> Client, std::map<const int, User> user, Server *serv, User user_send) {
	std::vector<std::string> allBuff = serv->_allBuff;
	std::string cmd = *(allBuff.begin());
	allBuff.erase(allBuff.begin());
	std::map<std::string, int> tmp;
	for (std::map<const int, User>::iterator it_u = user.begin() ; it_u != user.end(); it_u++) {
		tmp[it_u->second.getNickname()] = it_u->first;
	}
	for (std::vector<std::string>::iterator it_find = Client.begin() ; it_find != Client.end() ; it_find++) {
		std::map<std::string, int>::iterator it_tmp = tmp.find(*it_find);
		if (it_find->c_str()[0] == '#') {
			searchChannel(*it_find, serv, user_send, tmp);
		}
		else if (it_tmp == tmp.end()) {
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


void	notice(Server *serv, User user) {
	if (serv->_allBuff.size() <= 2) {
		std::string nick;
		if (user.getValidUser() == false) nick = "*"; else nick = user.getNickname();
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), nick);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (serv->_allBuff.size() > 2 && user.getValidUser() == false) {
		std::string msg = NAME + ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		std::vector<std::string> client;
		std::vector<std::string>::iterator it_buff = ++serv->_allBuff.begin();
		splitCmdClient(client, *it_buff);
		search_clientRPL(client, serv->_users, serv, user);
	}
}