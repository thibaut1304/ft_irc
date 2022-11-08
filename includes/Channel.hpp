/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:17:42 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/07 21:28:43 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Header.hpp>
#include <Users.hpp>

class       Channel
{
public:
	typedef User*                    UserPtr;
	typedef std::string              string;
	typedef std::set<UserPtr>        set_of_users;
	typedef std::map<string,UserPtr> map_users;

	// typedef std::vector<UserPtr> vector_of_users;

private:
	string _name;
	string _passwd;
	string _topic;
	std::map<std::string, UserPtr> _users, _users_banned, _users_invited;
	UserPtr _channelAdmin;

	bool _invite_only;
	bool _passwd_required;

public:
	Channel  (string  ChannelName, UserPtr ChannelAdmin);
	Channel  (string  ChannelName, UserPtr ChannelAdmin, string passwd);
	Channel  (Channel const        &other);
	~Channel ();

	void        addUser     (UserPtr     user);
	void        banUser     (std::string nickname);
	void        unbanUser   (std::string nickname);
	void        removeUser  (std::string nickname);
	int         isInChannel (std::string nickname);
	int         isBanned    (std::string nickname);
	int         isInvited   (std::string nickname);
	std::string getName     ();

	bool is_invite_only_channel   ();
	bool is_password_only_channel ();
	bool checkPassword            (std::string password);
	void sendToAll                (UserPtr     user, std::string command);

	void   setTopic (string str);
	string getTopic (void);

	std::map<std::string, Channel::UserPtr> getUsers        (void);
	std::map<std::string, Channel::UserPtr> getUsersBanned  (void);
	std::map<std::string, Channel::UserPtr> getUsersInvited (void);

	void printUsers(void)
	{
		map_users map = getUsers();
		map_users::iterator it  = map.begin();
		map_users::iterator ite = map.end();

		while (it != ite)
		{
			std::cout << (*it).first << std::endl;
			it++;
		}
	}
};
