/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:45 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/16 16:31:18 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define MSG6 (NAME + ERR_NEEDMOREPARAMS("INVITE", user.getNickname()))
#define MSG7 (ERR_NOSUCHNICK(user.getNickname(), serv->_allBuff[1]))
#define MSG8 (ERR_NOSUCHCHANNEL(user.getNickname(), serv->_allBuff[1]))
#define MSG9 (ERR_NOTONCHANNEL(user.getNickname(), serv->_allBuff[2]))
#define MSG10 (ERR_CHANOPRIVSNEEDED(user.getNickname(), serv->_allBuff[2]))
#define MSG11 (RPL_INVITING(user.getNickname(), serv->_allBuff[2], serv->_allBuff[1]))
#define MSG12 (user.getNickname() + "!" + user.getUsername() + "@" + user.getIp() + " INVITE :" + serv->_allBuff[2] + "\r\n")

void invite(Server *serv, User user)
{
  	if (!check_ERR_NEEDMOREPARAMS(serv, user) || !check_ERR_NOTREGISTERED(serv, user))
		return;
    else if (serv->_allBuff.size() == 2)
        return;
    else
    {
        if (!serv->getUser(serv->_allBuff[1]))
           send(user.getFd(), MSG7.c_str(), MSG7.length(), 0);
        else if (!serv->does_channel_exist(serv->_allBuff[2]))
           send(user.getFd(), MSG8.c_str(), MSG8.length(), 0);
        else if (!serv->getChannel(serv->_allBuff[2])->isInChannel(user.getNickname()))
           send(user.getFd(), MSG9.c_str(), MSG9.length(), 0);
        else if (!serv->getChannel(serv->_allBuff[2])->isAdmin(user.getNickname()))
           send(user.getFd(), MSG10.c_str(), MSG10.length(), 0);
        else
          {
            serv->getChannel(serv->_allBuff[2])->inviteUser(serv->getUser(serv->_allBuff[1]));
           send(user.getFd(), MSG11.c_str(), MSG11.length(), 0);
           send(serv->getUser(serv->_allBuff[1])->getFd(), MSG12.c_str(), MSG12.length(), 0);
          }
    }
}
