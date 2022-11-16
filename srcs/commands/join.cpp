/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:06:44 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/16 14:29:51 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

static int charset(std::string charset, std::string str)
{
	for (std::string::iterator it = charset.begin(); it != charset.end(); it++)
		if (str[0] == *it)
			return (1);
	return 0;
}
void join(Server *serv, User user)
{
	Server::map_users::iterator _it = serv->_users.begin();
	Server::map_users::iterator _ite = serv->_users.end();
	for (; _it != _ite; _it++)
		if (_it->second.getNickname().compare(user.getNickname()) == 0)
			break;
	if (!check_ERR_NEEDMOREPARAMS(serv, user) || !check_ERR_NOTREGISTERED(serv, user))
		return;
	std::vector<std::string> channels, passwords;
	split(channels, serv->_allBuff[1], ",");
	split(passwords, serv->_allBuff[2], ",");
	for (size_t i = 0; i < channels.size(); i++)
	{
		
		if (!charset("&#", channels[i]) || channels[i].size() > 50)
		{
			std::string msg = NAME + ERR_BADCHANMASK(user.getNickname(), channels[i]);
			if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
				perror_and_exit("476");
		}
		else if (serv->does_channel_exist(channels[i]))
		{
			std::map<std::string, Channel *>::iterator it = serv->_channels.find(channels[i]);
			if (it->second->isInChannel(user.getNickname()))
				serv->_allBuff[1].erase(serv->_allBuff[1].find(it->first),(it->first.size() + 1));
			else if (it->second->is_invite_only_channel() && !it->second->isInvited(user.getNickname()))
			{
				std::string msg = NAME + ERR_INVITEONLYCHAN(user.getNickname(), channels[i]);
				if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
					perror_and_exit("473");
			}
			else if (it->second->is_password_only_channel() && !it->second->checkPassword(passwords[i]))
			{
				std::string msg = NAME + ERR_BADCHANNELKEY(user.getNickname(), channels[i]);
				if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
					perror_and_exit("475");
			}
			else
			{
				it->second->addUser(&(_it->second));
				names(serv, (_it->second));
			}
		}
		else
		{
			serv->addChannel(channels[i], &(_it->second));
			names(serv, (_it->second));
		}
	}
}
