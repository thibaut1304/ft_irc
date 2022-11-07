/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:45 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/07 13:49:53 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

void invite(Server *serv, User user)
{
    if (serv->_allBuff.size() == 1)
    {
        std::string msg = NAME + ERR_NEEDMOREPARAMS("INVITE", user.getNickname());
        if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
            perror_and_exit("476");
    }
    else if (serv->_allBuff.size() == 2)
    {
        
    }

}
