/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:17:42 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/05 17:12:59 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Header.hpp>
#include <Users.hpp>

class Channel
{
	public:
		typedef User*                UserPtr;
		typedef std::string          string;
		typedef std::set<UserPtr>    set;
		typedef std::vector<UserPtr> vector;

private:
    string  _name;
    string  _passwd;
	string  _topic;

	set     _invited_users;
    set     _users;

	UserPtr _channelAdmin;

	bool    _invite_only;
    bool    _passwd_required;
    vector  _banned_users;

public:

    Channel(string ChannelName, UserPtr ChannelAdmin);
    Channel(string ChannelName, UserPtr ChannelAdmin, string passwd);
    Channel(Channel const &other);
    ~Channel();

    int addUser     (UserPtr user);
    int isInChannel (UserPtr user);
};
