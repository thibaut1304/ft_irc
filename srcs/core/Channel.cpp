/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:53 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/04 18:26:01 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Channel.hpp>

// static void print_set(std::set<User *> &lst)
// {
//     if (!lst.empty())
//     {
//         for (std::set<User *>::iterator it = lst.begin(); it != lst.end(); it++)
//         {
//             std::cout << (*it)->getNickname() << '\n';
//         }
//         std::cout << std::endl;
//     }
//     else
//         std::cout << "This set is empty ... :(" << std::endl;
// }
Channel::Channel(std::string ChannelName, User *channelAdmin) : _name(ChannelName), _passwd(""), _channelAdmin(channelAdmin), _invite_only(false), _passwd_required(false)
{
    // std::cout << "Channel created successfully, name =" << ChannelName << "_passwd" << _passwd << "channelAdmin" << _channelAdmin->getNickname() << "_invite_only = " << _invite_only << "_passwd_required = " << _passwd_required << std::endl;
    _users.insert(channelAdmin);

    // print_set(_users);
}

Channel::Channel(std::string ChannelName, User *channelAdmin, std::string passwd) : _name(ChannelName), _passwd(passwd), _channelAdmin(channelAdmin), _invite_only(false), _passwd_required(true)
{
}
Channel::Channel(Channel const &other)
{
    _name = other._name;
    _passwd = other._passwd;
    _channelAdmin = other._channelAdmin;
    _invite_only = other._invite_only;
    _passwd_required = other._passwd_required;
}
Channel::~Channel()
{
}
int Channel::addUser(User *user)
{
    _users.insert(user);
    return (0);
}
int Channel::isInChannel(User *user)
{
    return (_users.find(user) != _users.end());
}
//        ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//        ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//        ERR_CHANNELISFULL               ERR_BADCHANMASK
//        ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//        RPL_TOPIC