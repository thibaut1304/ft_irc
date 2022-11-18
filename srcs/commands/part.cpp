/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:25:04 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/16 16:29:54 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

#define PART_MSG1 (ERR_NOSUCHCHANNEL(user.getNickname(), serv->get_buff()[1]))

void part(Server *serv, User user)
{
    if (!check_ERR_NEEDMOREPARAMS(serv, user) || !check_ERR_NOTREGISTERED(serv, user))
        return;
    std::vector<std::string> channels;
    split(channels, serv->get_buff()[1], ",");
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (!serv->does_channel_exist(channels[i]))
            send(user.getFd(), PART_MSG1.c_str(), PART_MSG1.length(), 0);
        else
        {
            serv->getChannel(channels[i])->removeUser(&user);
            if (serv->getChannel(channels[i])->getUsers().size() == 0)
                serv->deleteChannel(channels[i]);
        }
    }
}
