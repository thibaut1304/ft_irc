/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:31:45 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/18 15:18:04 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define KICK_MSG1 (NAME + ERR_NEEDMOREPARAMS("KICK", user.getNickname()))
#define KICK_MSG2 (ERR_NOSUCHCHANNEL(user.getNickname(), serv->get_buff()[1]))
#define KICK_MSG3 (ERR_NOSUCHNICK(user.getNickname(), serv->get_buff()[1]))
#define KICK_MSG4 (ERR_CHANOPRIVSNEEDED(user.getNickname(), serv->get_buff()[1]))
#define KICK_MSG5 (ERR_NOTONCHANNEL(user.getNickname(), serv->get_buff()[2]))

void kick(Server *serv, User user)
{
    if (!check_ERR_NOTREGISTERED(serv, user))
        return;
    else if (serv->get_buff().size() < 3)
           send(user.getFd(), KICK_MSG1.c_str(), KICK_MSG1.length(), 0);
    else if (!serv->does_channel_exist(serv->get_buff()[1]))
           send(user.getFd(), KICK_MSG2.c_str(), KICK_MSG2.length(), 0);
    else if (!serv->getUser(serv->get_buff()[2]))
           send(user.getFd(), KICK_MSG3.c_str(), KICK_MSG3.length(), 0);
    else if (!serv->getChannel(serv->get_buff()[1])->isAdmin(user.getNickname())  && !serv->is_server_operator(user.getNickname())) 
           send(user.getFd(), KICK_MSG4.c_str(), KICK_MSG4.length(), 0);
    else if (!serv->getChannel(serv->get_buff()[1])->isInChannel(user.getNickname()) && !serv->is_server_operator(user.getNickname()))
           send(user.getFd(), KICK_MSG5.c_str(), KICK_MSG5.length(), 0);
    else
            serv->getChannel(serv->get_buff()[1])->removeUser(serv->getUser(serv->get_buff()[2]));
}

