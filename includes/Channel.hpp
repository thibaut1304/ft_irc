/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:17:42 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/07 13:09:03 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Header.hpp>
#include <Users.hpp>

class Channel
{
public:
	typedef User *UserPtr;
	typedef std::string string;
	typedef std::set<UserPtr> set_of_users;

	// typedef std::vector<UserPtr> vector_of_users;

private:
	string _name;
	string _passwd;
	string _topic;

	set_of_users _users;
	set_of_users _users_banned;
	set_of_users _users_invited;

	UserPtr _channelAdmin;

	bool _invite_only;
	bool _passwd_required;

	// vector_of_users _banned_users;
	// set_of_users    _invited_users;

public:
	Channel(string ChannelName, UserPtr ChannelAdmin);
	Channel(string ChannelName, UserPtr ChannelAdmin, string passwd);
	Channel(Channel const &other);
	~Channel();

	int addUser(UserPtr user);
	int removeUser(UserPtr user);
	int banUser(UserPtr user);
	int unbanUser(UserPtr user);

	int isInChannel(UserPtr user);
	int isBanned(UserPtr user);
	int isInvited(UserPtr user);

	bool is_invite_only_channel();
	bool is_password_only_channel();
	bool checkPassword(std::string password);

	void setTopic(string str);
	string getTopic(void);

	set_of_users getUsers(void);
	set_of_users getUsersBanned(void);
	set_of_users getUsersInvited(void);
};
