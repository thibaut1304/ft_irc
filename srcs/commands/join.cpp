/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:06:44 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/07 21:49:32 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>

static int charset(std::string charset, std::string str)
{
  for (std::string::iterator it = charset.begin(); it != charset.end(); it++)
    if (str[0] == *it)
      return (1);
  return 0;
}
void perror_and_exit(std::string code)
{
  std::string error = "Error send msg ";
  error.append(code);
  perror(error.c_str());
  exit(errno);
}
void join(Server *serv, User user)
{

  if (!check_ERR_NEEDMOREPARAMS(serv, user))
    return;
  std::vector<std::string> channels, passwords;
  split(channels, serv->_allBuff[1], ",");
  split(passwords, serv->_allBuff[2], ",");
  for (size_t i = 0; i < channels.size(); i++)
  {
    if (!charset("&#", channels[i]) || channels[i].size() > 50)
    {
      std::string msg = NAME + ERR_BADCHANMASK(user.getNickname(), channels[i]);
      if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
        perror_and_exit("476");
    }
    else if (serv->does_channel_exist(channels[i]))
    {
      std::map<std::string, Channel *>::iterator it = serv->_channels.find(channels[i]);
      if (it->second->is_invite_only_channel() && it->second->isInvited(user.getNickname()))
      {
        std::string msg = NAME + ERR_INVITEONLYCHAN(user.getNickname(), channels[i]);
        if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
          perror_and_exit("473");
      }
      else if (it->second->is_password_only_channel() && it->second->checkPassword(passwords[i]))
      {
        std::string msg = NAME + ERR_BADCHANNELKEY(user.getNickname(), channels[i]);
        if (send(user.getFd(), msg.c_str(), msg.length(), 0) < 0)
          perror_and_exit("475");
      }
      else
        it->second->addUser(&user);
      std::cout << "channel found" << std::endl;
    }
    else
    {
      std::cout << "didnt find channel" << std::endl;
      serv->addChannel(channels[i], &user);
    }
  }
  std::map<std::string, Channel *> schannels = serv->getChannels();
  std::map<std::string, Channel *>::iterator it = schannels.begin();
  for (; it != schannels.end(); it++)
    std::cout << it->second->getName() << std::endl;
}