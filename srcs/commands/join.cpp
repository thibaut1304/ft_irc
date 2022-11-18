/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:06:44 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/16 16:15:33 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define JOIN_MSG1 ( NAME + ERR_BADCHANMASK(user.getNickname(), channels[i]))
#define JOIN_MSG2 ( NAME + ERR_INVITEONLYCHAN(user.getNickname(), channels[i]))
#define JOIN_MSG3 ( NAME + ERR_BADCHANNELKEY(user.getNickname(), channels[i]))

static int charset(std::string charset, std::string str)
{
	for (std::string::iterator it = charset.begin(); it != charset.end(); it++)
		if (str[0] == *it)
			return (1);
	return 0;
}
void join(Server *serv, User user)
{
	Server::map_users::iterator _it = serv->get_users().begin();
	Server::map_users::iterator _ite = serv->get_users().end();
	for (; _it != _ite; _it++)
		if (_it->second.getNickname().compare(user.getNickname()) == 0)
			break;
	if (!check_ERR_NEEDMOREPARAMS(serv, user) || !check_ERR_NOTREGISTERED(serv, user))
		return;
	std::vector<std::string> channels, passwords;
	split(channels, serv->get_allBuff()[1], ",");
	split(passwords, serv->get_allBuff()[2], ",");
	for (size_t i = 0; i < channels.size(); i++)
	{
		
		if (!charset("&#", channels[i]) || channels[i].size() > 50)
			send(user.getFd(), JOIN_MSG1.c_str(), JOIN_MSG1.length(), 0);
		else if (serv->does_channel_exist(channels[i]))
		{
			std::map<std::string, Channel *>::iterator it = serv->get_channels().find(channels[i]);
			if (it->second->isInChannel(user.getNickname()))
				serv->get_allBuff()[1].erase(serv->get_allBuff()[1].find(it->first),(it->first.size() + 1));
			else if (it->second->is_invite_only_channel() && !it->second->isInvited(user.getNickname()) && !serv->is_server_operator(user.getNickname())) 
				send(user.getFd(), JOIN_MSG2.c_str(), JOIN_MSG2.length(), 0);
			else if (it->second->is_password_only_channel() && !it->second->checkPassword(passwords[i]) && !serv->is_server_operator(user.getNickname())) 
				send(user.getFd(), JOIN_MSG3.c_str(), JOIN_MSG3.length(), 0);
			else
				it->second->addUser(&(_it->second));
		}
		else
			serv->addChannel(channels[i], &(_it->second));
	}
	names(serv, (_it->second));
}
