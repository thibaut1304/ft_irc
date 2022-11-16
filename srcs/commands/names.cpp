/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:47:14 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/16 16:20:38 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define NAMES_MSG1 (RPL_ENDOFNAMES(user.getNickname(), "*"))
#define NAMES_MSG2 (ERR_NOSUCHCHANNEL(user.getNickname(), channels[i]))
#define NAMES_MSG3 (RPL_NAMREPLY(user.getNickname(), channels[i], users))
#define NAMES_MSG4 (RPL_ENDOFNAMES(user.getNickname(), channels[i]))

void names(Server *serv, User user)
{
    if (serv->_allBuff.size() == 1)
        send(user.getFd(), NAMES_MSG1.c_str(), NAMES_MSG1.length(), 0);
    else if (!check_ERR_NOTREGISTERED(serv, user))
        return;
    else
    {
        std::vector<std::string> channels;
        split(channels, serv->_allBuff[1], ",");

        for (size_t i = 0; i < channels.size(); i++)
        {
            if (!serv->does_channel_exist(channels[i]))
                send(user.getFd(), NAMES_MSG2.c_str(), NAMES_MSG2.length(), 0);
            else
            {
                std::string users;
                std::map<std::string, User *> tmp = serv->getChannel(channels[i])->getAdmin();
                std::map<std::string, User *>::iterator it = tmp.begin();
                std::map<std::string, User *>::iterator ite = tmp.end();
                while (it != ite)
                {
                    users.append("@").append(it->first).append(" ");
                    it++;
                }
                std::map<std::string, User *> tmp2 = serv->getChannel(channels[i])->getUsers();
                std::map<std::string, User *>::iterator itu = tmp2.begin();
                std::map<std::string, User *>::iterator itue = tmp2.end();
                while (itu != itue)
                {
                    if (tmp.find(itu->first) != tmp.end())
                        itu++;
                    else
                    {
                        users.append(itu->first);
                        users.append(" ");
                        itu++;
                    }
                }
                send(user.getFd(), NAMES_MSG3.c_str(), NAMES_MSG3.length(), 0);
                send(user.getFd(), NAMES_MSG4.c_str(), NAMES_MSG4.length(), 0);
            }
        }
    }
}