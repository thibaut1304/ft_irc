/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:39:04 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/02 16:39:06 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Header.hpp>
#include <Users.hpp>

class Channel
{
private:
    std::string _name;
    std::string _passwd;
    User *_channelAdmin;
    std::set<User *> _invited_users;
    std::set<User *> _users;
    // std::vector<User*> _banned_users;
    bool _invite_only;
    bool _passwd_required;

public:
    Channel(std::string ChannelName, User *ChannelAdmin);
    Channel(std::string ChannelName, User *ChannelAdmin, std::string passwd);
    Channel(Channel const &other);
    ~Channel();

    int addUser(User *user);
    int isInChannel(User *user);
};