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
User *channelAdmin;
public:
    Channel(std::string ChannelName, User *ChannelAdmin);
    Channel(Channel const &other);
    Channel &operator=(Channel const &other);
    ~Channel();

    int addUser(User *user);

};