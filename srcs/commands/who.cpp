/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:39:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/18 11:20:06 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

static void recordAdminChannel(Server *serv, std::map<std::string, User *> & userChannel, std::string chan = "") {
	userChannel.clear();
	std::map<std::string, Channel *>::iterator it_chan = serv->_channels.begin();
	bool test = false;
	if (chan.compare("") != 0)
		test = true;
	for (; it_chan != serv->_channels.end() ; it_chan++) {
		std::map<std::string, User *> admin = it_chan->second->getAdmin();
		std::map<std::string, User *>::iterator it_admin = admin.begin();
		for (;it_admin != admin.end();it_admin++) {
			if (!test)
				userChannel[it_chan->second->getName()] = it_admin->second;
			else if (it_chan->first.compare(chan) == 0)
				userChannel[it_chan->second->getName()] = it_admin->second;
		}
	}
}

static void	printAllUser(Server *serv, User user) {
	std::string tmp_channel = "*";
	std::string tmp_chan 	= "@";

	std::map<std::string, User *> userChannel;
	recordAdminChannel(serv, userChannel);

	std::map<std::string, std::string> tmp;
	std::map<std::string, User *>::iterator it_chan = userChannel.begin();
	for (; it_chan != userChannel.end(); it_chan++) {
		if (tmp.find(it_chan->second->getNickname()) == tmp.end()) {
			std::string msg = RPL_WHOREPLY352(	user.getNickname(), \
												it_chan->first, \
												it_chan->second->getUsername(), \
												it_chan->second->getIp(), it_chan->second->getNickname(), tmp_chan, \
												it_chan->second->getHostname(), it_chan->second->getFullName());
			send(user.getFd(), msg.c_str(), msg.length(), 0);
			tmp[it_chan->second->getNickname()] = it_chan->first;
		}
	}
	tmp_chan = " ";
	std::map<const int, User>::iterator it_user = serv->getUsers().begin();
	for (;it_user != serv->getUsers().end(); it_user++) {
		if (tmp.find(it_user->second.getNickname()) == tmp.end()) {
			std::string msg = RPL_WHOREPLY352(	user.getNickname(), \
												tmp_channel, \
												it_user->second.getUsername(), \
												it_user->second.getIp(), it_user->second.getNickname(), tmp_chan, \
												it_user->second.getHostname(), it_user->second.getFullName());
			send(user.getFd(), msg.c_str(), msg.length(), 0);
		}
	}
	std::string msg_315 = RPL_ENDOFWHO(user.getNickname(), std::string("*"));
	send(user.getFd(), msg_315.c_str(), msg_315.length(), 0);
}

static void	printUser(Server *serv, User user, std::string nick) {
	std::string tmp_channel = "*";
	std::string tmp_chan 	= " ";

	std::string arg = print_allBuff(serv->get_buff());

	std::map<const int, User>::iterator it;
	for (it = serv->getUsers().begin() ; it != serv->getUsers().end(); it++)
		if (it->second.getNickname().compare(nick) == 0)
			break ;
	if (it == serv->getUsers().end())
		if (arg[0] != '#') {
			std::string msg_315 = RPL_ENDOFWHO(user.getNickname(), nick);
			send(user.getFd(), msg_315.c_str(), msg_315.length(), 0);
			return ;
		}
	if (arg[0] == '#') {

		std::map<std::string, Channel *>::iterator it_chan_name = serv->_channels.begin();
		for (;it_chan_name != serv->_channels.end();it_chan_name++)
			if (it_chan_name->first.compare(arg) == 0)
				break ;
		if (it_chan_name == serv->_channels.end()) {
			std::string msg_315 = RPL_ENDOFWHO(user.getNickname(), nick);
			send(user.getFd(), msg_315.c_str(), msg_315.length(), 0);
			return ;
		}
		std::map<std::string, User *> userChannel;
		recordAdminChannel(serv, userChannel, it_chan_name->first);
		std::map<std::string, User *>::iterator it_chan = userChannel.begin();
		std::map<std::string, std::string> tmp;
		for (; it_chan != userChannel.end(); it_chan++) {
			std::map<std::string, Channel *>::iterator it_tmp_chan = serv->_channels.find(it_chan->first);
			std::map<std::string, User *> user_in_chan = it_tmp_chan->second->getUsers();
			std::map<std::string, User *>::iterator it_user_in_chan = user_in_chan.begin();
			for (;it_user_in_chan != user_in_chan.end() ; it_user_in_chan++) {
				if (tmp.find(it_user_in_chan->second->getNickname()) == tmp.end()) {
					std::map<std::string, User *> tmp_admin = it_tmp_chan->second->getAdmin();
					std::map<std::string, User *>::iterator it_tmp_admin = tmp_admin.begin();
					if (it_tmp_admin->first.compare(it_user_in_chan->first) == 0)
						tmp_chan = "@";
					else
						tmp_chan = " ";
					std::string msg = RPL_WHOREPLY352(	user.getNickname(), \
														it_chan->first, \
														it_user_in_chan->second->getUsername(), \
														it_user_in_chan->second->getIp(), it_user_in_chan->second->getNickname(), tmp_chan, \
														it_user_in_chan->second->getHostname(), it_user_in_chan->second->getFullName());
					send(user.getFd(), msg.c_str(), msg.length(), 0);
					tmp[it_user_in_chan->second->getNickname()] = it_chan->first;
				}
			}
		}
	}
	else {
		std::string msg = RPL_WHOREPLY352(	user.getNickname(), \
											tmp_channel, \
											it->second.getUsername(), \
											it->second.getIp(), \
											it->second.getNickname(), tmp_chan, \
											it->second.getHostname(), it->second.getFullName());
		send(user.getFd(), msg.c_str(), msg.length(), 0);
			}
	std::string msg_315 = RPL_ENDOFWHO(user.getNickname(), nick);
	send(user.getFd(), msg_315.c_str(), msg_315.length(), 0);
}

static void	recupNick(std::string & nick, std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = ++buff.begin();
	nick = *it;
}

void	who(Server *serv, User user) {
	if (serv->get_buff().size() == 1) {
		std::string nick = "*";
		if (user.getValidUser() == true)
			nick =	user.getNickname();
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->get_buff()), nick);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		std::string nick;
		recupNick(nick, serv->get_buff());
		if (!nick.compare("*") || !nick.compare("0"))
			printAllUser(serv, user);
		else
			printUser(serv, user, nick);
	}
}
