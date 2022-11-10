/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:00:39 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/10 15:40:27 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

void list(Server *serv, User user)
{
    std::string usernames;
    std::map<std::string, Channel *> tmp = serv->getChannels();
    if (serv->_allBuff.size() == 1)
    {
            std::string msg = RPL_LISTSTART(user.getNickname());
            send(user.getFd(), msg.c_str(), msg.length(), 0);
        for (std::map<std::string, Channel *>::iterator it = tmp.begin(); it != tmp.end(); it++)
        {
            usernames.clear();
            std::map<std::string, User *>::iterator it_user = it->second->getUsers().begin();
            std::map<std::string, User *>::iterator it_user_end = it->second->getUsers().begin();
            while (it_user != it_user_end)
            {
                usernames += " " + it_user->first;
                it_user++;
            }
            std::string msg = RPL_LIST(user.getNickname(), it->first, usernames, "");
            send(user.getFd(), msg.c_str(), msg.length(), 0);
        }
    }
    std::string msg = RPL_LISTEND(user.getNickname());
    send(user.getFd(), msg.c_str(), msg.length(), 0);
}