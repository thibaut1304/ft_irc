/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:17:42 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 20:45:08 by adlancel         ###   ########.fr       */
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
    bool is_invite_only();
    bool is_pass_required();

    void addUser(User *user);
    int isInChannel(User *user);
};