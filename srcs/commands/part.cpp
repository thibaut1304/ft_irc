/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:25:04 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/18 15:38:28 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define PART_MSG1 (ERR_NOSUCHCHANNEL(user.getNickname(), serv->get_allBuff()[1]))

void part(Server *serv, User user)
{
    if (!check_ERR_NEEDMOREPARAMS(serv, user) || !check_ERR_NOTREGISTERED(serv, user))
        return;
    std::vector<std::string> channels;
    split(channels, serv->get_allBuff()[1], ",");
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (!serv->does_channel_exist(channels[i]))
            send(user.getFd(), PART_MSG1.c_str(), PART_MSG1.length(), 0);
        else
        {
            if (serv->getChannel(channels[i])->isAdmin(user.getNickname()))
                serv->getChannel(channels[i])->removeAdmin(user.getNickname());
            serv->getChannel(channels[i])->removeUser(&user);

            if (serv->getChannel(channels[i])->getSize() == 0)
                serv->deleteChannel(channels[i]);
        }
    }
}
