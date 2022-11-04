/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:06:44 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/04 14:33:09 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void join(Server *serv, User user)
{
  (void)user;
  std::vector<std::string> channels;
  for (size_t i = 0; i < serv->_allBuff.size(); i++)
    std::cout << serv->_allBuff[i] << std::endl;
  switch (serv->_allBuff.size())
  {
  case 2:
  {
    split(channels, serv->_allBuff[1], ",");
    std::cout << "join called" << std::endl;
    std::cout << channels.size() << std::endl;
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
      std::cout << "channels = " << *it << std::endl;
    break;
  }
  default:
    break;
  }

  {
  }
  // switch (serv->_allBuff.size())
  // {
  // case 1:
  // {
  //     std::string msg = NAME + ERR_NEEDMOREPARAMS(print_allBuff(serv->_allBuff));
  //     send(user.getFd(), msg.c_str(), msg.length(), 0);
  //     break;
  // }

  // case 2:
  // {
  //     std::map<std::string, Channel>::iterator it = _channels.find(_allBuff[2]);
  //     if (it != _channels.end())
  //     {
  //         // check if mdp
  //         if ()
  //         // check if invite only
  //         // join existing channel;
  //         break;
  //     }
  //     else
  //     {
  //     std::string msg = NAME + ERR_NOSUCHCHANNEL(print_allBuff(serv->_allBuff));
  //     send(user.getFd(), msg.c_str(), msg.length(), 0);

  //     }
  // }

  // case 3:
  //     break;

  // default:
  //     break;
  // }
  // ERR_TOOMANYCHANNELS
  //  serv.createChannel()
}
