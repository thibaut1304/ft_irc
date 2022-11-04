/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:06:44 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/04 22:24:42 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>
int charset(std::string charset, std::string str)
{
  int i = 0;
  while (charset[i])
  {
    if (str[0] == charset[i])
      return (1);
    i++;
  }
  return (0);
}
static int check_rights(Channel channel)
{
  int i = 0;
  std::string msg = NAME;
  if (channel.is_invite_only())
  {
    ERR_INVITEONLYCHAN()
    i += 1;
  }
  else if (channel.is_pass_required())
  {
    i += 1;
    `
  }
  return i;
}
void join(Server *serv, User user)
{

  std::vector<std::string> channels;
  split(channels, serv->_allBuff[1], ",");

  switch (serv->_allBuff.size())
  {
  case 1:
  {
    std::string msg = NAME + ERR_NEEDMOREPARAMS("JOIN", user.getNickname());
    if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
    {
      perror("Error send msg 461");
      exit(errno);
    }
    break;
  }
  case 2:
  {
    for (size_t i = 0; i < channels.size(); i++)
    {

      if (!charset("&#!+", channels[0]) || channels[0].size() > 50)
      {
        std::string msg = NAME + ERR_BADCHANMASK(user.getNickname(), channels[i]);
        if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
        {
          perror("Error send msg 476");
          exit(errno);
        }
      }
      else if (serv->_channels.contains(channels[i]))
      {
        if (!check_rights(serv->_channels[channels[i]]))
          serv->_channels[channels[i]].addUser(user);
        else

        // send
      }
      else
        serv->_channels.insert(make_pair(channels[i], Channel(channels[i], &user)));
    }
  }
  case 3:
  {
  }
  default:
  }

  // std::cout << "le buff contient [" << i << "]" << channels[i] << std::endl;
  //  serv.createChannel()

  // switch (serv->_allBuff.size())
  // {
  // case 2:
  // {
  //   split(channels, serv->_allBuff[1], ",");
  //   std::cout << "join called" << std::endl;
  //   std::cout << channels.size() << std::endl;
  //   for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
  //     std::cout << "channels = " << *it << std::endl;
  //   break;
  // }
  // default:
  //   break;
  // }

  // {
  // }
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
  //         if ()`
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
}
