/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:45 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/10 22:50:17 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define MSG1 (NAME + ERR_NEEDMOREPARAMS("INVITE", user.getNickname()))
#define MSG2 (ERR_NOSUCHNICK(user.getNickname()), serv->_allbuff[1])
#define MSG3 (ERR_NOSUCHCHANNEL(user.getNickname()), serv->_allbuff[1])
#define MSG4 (ERR_NOTONCHANNEL(user.getNickname()), serv->_allbuff[2])
#define MSG4 (ERR_CHANOPRIVSNEEDED(user.getNickname(), serv->_allBuff[2]))
void invite(Server *serv, User user)
{
    if (serv->_allBuff.size() == 1)
    {
        if (send(user.getFd(), MSG1.c_str(), MSG1.length(), 0) < 0)
            perror_and_exit("476");
    }
    else if (serv->_allBuff.size() == 2)
        return ;
    else 
    {
        if (!serv.getUser(_allbuff[1]))
            if (send(user.getFd(), MSG2.c_str(), MSG2.length(), 0) < 0)
                perror_and_exit("401");
        else if (!serv->does_channel_exist(serv->_allBuff[2]))
            if (send(user.getFd(), MSG3.c_str(), MSG3.length(), 0) < 0)
                perror_and_exit("401");
        else if (!serv->getChannel(serv->_allBuff[2]).isInChannel(user.getNickname()))
            if (send(user.getFd(), MSG4.c_str(), MSG4.length(), 0) < 0)
                perror_and_exit("401");
        else if (!serv->getChannel(serv->_allBuff[2]).isAdmin(user.getNickname()))
            if (send(user.getFd(), MSG5.c_str(), MSG5.length(), 0) < 0)
                perror_and_exit("401");
        else 
            serv->getChannel(serv->_allBuff[2]).inviteUser();
        
        std::vector<std::string> channels;
        split(channel, serv->_allBuff[2], ',');
    }
    
}
