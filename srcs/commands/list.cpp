/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:00:39 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/10 19:22:25 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>
#include <string>

#define MSG1 (RPL_LISTSTART(user.getNickname()))
#define MSG2 (RPL_LIST(user.getNickname(), channel, to_string(it->second->numberOfUsers()), options, topic))
#define MSG3 (RPL_LISTEND(user.getNickname()))

static std::string to_string(const int n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
static std::string get_options_from_channel(Channel *chan)
{
    std::string options = "[";

    if (chan->get_is_private())
        options.append("p");
    if (chan->get_is_secret())
        options.append("s");
    if (chan->get_is_invite_only())
        options.append("i");
    if (chan->get_is_topic_unlocked() == false)
        options.append("t");
    if (chan->get_is_moderated())
        options.append("m");
    if (chan->get_mute_non_moderators())
        options.append("v");
    if (options.length() != 1)
        options.insert(1, "+");
    options.append("]");
    return (options);
}

void list(Server *serv, User user)
{
    std::string options = "";
    std::string topic = "";
    std::map<std::string, Channel *> tmp = serv->getChannels();
    if (serv->_allBuff.size() == 1)
    {
        std::string channel = "*";
        send(user.getFd(), MSG1.c_str(), MSG1.length(), 0);
        for (std::map<std::string, Channel *>::iterator it = tmp.begin(); it != tmp.end(); it++)
        {
            if (!it->second->get_is_secret() || it->second->isInChannel(user.getNickname()))
            {
                if (!it->second->get_is_private() || it->second->isInChannel(user.getNickname()))
                {
                    channel.erase(0).insert(0, it->second->getName());
                    options = get_options_from_channel(it->second);
                    topic = it->second->getTopic();
                }
                send(user.getFd(), MSG2.c_str(), MSG2.length(), 0);
            }
        }
    }
    send(user.getFd(), MSG3.c_str(), MSG3.length(), 0);
}
