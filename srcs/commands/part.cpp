/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:25:04 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/14 16:05:37 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

void part(Server *serv, User user)
{
    if (!check_ERR_NEEDMOREPARAMS(serv, user))
        return;
    std::vector<std::string> channels;
    split(channels, serv->_allBuff[1], ",");

    for (size_t i = 0; i < channels.size(); i++)
    {
        if (!check_ERR_NOSUCHCHANNEL(serv, user) || !check_ERR_NOTONCHANNEL(serv, user))
            ;
        else
        {
            std::cout << "part called ok" << std::endl;
            serv->getChannel(channels[i])->removeUser(&user);
            
            if (serv->getChannel(channels[i])->getUsers().size()== 0)
                serv->deleteChannel(channels[i]);
            
        }
    }
}
