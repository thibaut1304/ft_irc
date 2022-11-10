/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:47:14 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/10 14:00:22 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

void names_one_param(User user)
{
    std::string msg = RPL_ENDOFNAMES(user.getNickname());
    send(user.getFd(), msg.c_str(), msg.length(), 0);
}

void names(Server *serv, User user)
{
    std::string msg;
    if (serv->_allBuff.size() == 1)
        names_one_param(user);
    else
    {
        std::vector<std::string> channels;
        split(channels, serv->_allBuff[1], ",");

        for (size_t i = 0; i < channels.size(); i++)
        {
            if (!serv->does_channel_exist(channels[i]))
            {
                msg = NAME + ERR_NOSUCHCHANNEL(channels[i]);
                send(user.getFd(), msg.c_str(), msg.length(), 0);
            }
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
                        users.append(" ");
                        users.append(itu->first);
                        itu++;
                    }
                }

                msg = RPL_NAMREPLY(user.getNickname(), channels[i], users);
                send(user.getFd(), msg.c_str(), msg.length(), 0);
                names_one_param(user);
            }
        }
    }
}