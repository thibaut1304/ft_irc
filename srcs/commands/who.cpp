/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:39:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/12 20:37:27 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

// "<client> <channel> <username> <host> <server> <nick> <flags> :<hopcount> <realname>"
// :irc.local 352 qq * 1 172.17.0.1 irc.local qq H :0 4
// :irc.local 315 qq qq :End of /WHO list.
// RPL_WHOREPLY352(nick, channel, user, username, ip, chan, hostname, fullname)

static void recordAdminChannel(Server *serv, std::map<std::string, User *> & userChannel) {
	std::map<std::string, Channel *>::iterator it_chan = serv->_channels.begin();

	for (; it_chan != serv->_channels.end() ; it_chan++) {
		std::map<std::string, User *> admin = it_chan->second->getAdmin();
		std::map<std::string, User *>::iterator it_admin = admin.begin();
		userChannel[it_chan->second->getName()] = it_admin->second;
	}
}

static void	printAllUser(Server *serv, User user) {
	std::string tmp_channel = "*";
	std::string tmp_chan 	= "@";

	// Prendre la clefs nickname user valeur map de user * et channel
	// Nickname et name channel !
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
	tmp_chan = "";
	std::map<const int, User>::iterator it_user = serv->_users.begin();
	for (;it_user != serv->_users.end(); it_user++) {
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
	std::string tmp_chan 	= "";
	std::map<const int, User>::iterator it;
	for (it = serv->_users.begin() ; it != serv->_users.end(); it++) {
		if (it->second.getNickname().compare(nick) == 0)
			break ;
	}
	std::string msg = RPL_WHOREPLY352(	user.getNickname(), \
										tmp_channel, \
										it->second.getNickname(), it->second.getUsername(), \
										it->second.getIp(), tmp_chan, \
										it->second.getHostname(), it->second.getFullName());
	send(user.getFd(), msg.c_str(), msg.length(), 0);
	std::string msg_315 = RPL_ENDOFWHO(user.getNickname(), nick);
	send(user.getFd(), msg_315.c_str(), msg_315.length(), 0);
}

static void	recupNick(std::string & nick, std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = ++buff.begin();
	nick = *it;
}

void	who(Server *serv, User user) {
	if (serv->_allBuff.size() == 1) {
		std::string nick = "*";
		if (user.getValidUser() == true)
			nick =	user.getNickname();
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), nick);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {
		std::string nick;
		recupNick(nick, serv->_allBuff);
		if (!nick.compare("*") || !nick.compare("0"))
			printAllUser(serv, user);
		else
			printUser(serv, user, nick);
	}
}
