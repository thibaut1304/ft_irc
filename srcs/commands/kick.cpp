/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:31:45 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/16 16:47:12 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define KICK_MSG1 (NAME + ERR_NEEDMOREPARAMS("KICK", user.getNickname()))
#define KICK_MSG2 (ERR_NOSUCHCHANNEL(user.getNickname(), serv->_allBuff[1]))
#define KICK_MSG3 (ERR_NOSUCHNICK(user.getNickname(), serv->_allBuff[1]))

void kick(Server *serv, User user)
{
    if (!check_ERR_NOTREGISTERED(serv, user))
        return;
    else if (serv->_allBuff.size() < 3)
           send(user.getFd(), KICK_MSG1.c_str(), KICK_MSG1.length(), 0);
    else if (!serv->does_channel_exist(serv->_allBuff[1]))
           send(user.getFd(), KICK_MSG2.c_str(), KICK_MSG2.length(), 0);
    else if (!serv->getUser(serv->_allBuff[2]))
           send(user.getFd(), KICK_MSG3.c_str(), KICK_MSG3.length(), 0);
    else if 
    {
        if (serv->getChannel(serv->_allbuff[1]).isAdmin(user.getNickname()))
            serv->getChannel(serv->_allBuff[1]).removeUser(serv->_allBuff[2]);
    }
    
}

