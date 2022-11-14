/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:17:42 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/14 15:48:49 by thhusser         ###   ########.fr       */
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
	typedef std::map<string, UserPtr> map_users;

	// typedef std::vector<UserPtr> vector_of_users;

private:
	string _name;
	string _passwd;
	string _topic;
	std::map<std::string, UserPtr> _users, _users_banned, _users_invited, _channelAdmin;
	int _nbUsers;
	bool _invite_only;
	bool _passwd_required;

	/* ================================================================== */
	/* ------------------------- CHANNEL FLAGS -------------------------- */
	/* ================================================================== */

		//                                                      // o - give/take channel operator privileges;
		bool        _is_private;                                // p - private channel flag;
		bool        _is_secret;                                 // s - secret channel flag;
		bool        _is_invite_only;                            // i - invite-only channel flag;
		bool        _is_topic_unlocked;                         // t - topic settable by channel operator only flag;
		bool        _is_moderated;                              // m - moderated channel;
		bool        _mute_non_moderators;                       // v - give/take the ability to speak on a moderated channel;
		size_t      _user_limit;                                // l - set the user limit to channel;
		std::string _ban_mask;                                  // b - set a ban mask to keep users out;
		std::string _channel_key;                               // k - set a channel key (password).
		bool _is_accepting_messages_from_outside_client;		// n - no messages to channel from clients on the outside;
																////

public:
	Channel(string ChannelName, UserPtr ChannelAdmin);
	Channel(Channel const &other);
	~Channel();

	void addUser(UserPtr user);
	void inviteUser(UserPtr user);
	void banUser(std::string nickname);
	void unbanUser(std::string nickname);
	void removeUser(UserPtr user);
	int isInChannel(std::string nickname);
	int isBanned(std::string nickname);
	int isInvited(std::string nickname);
	int isAdmin(std::string nickname);
	int numberOfUsers();

	std::string getName();

	bool is_invite_only_channel();
	bool is_password_only_channel();
	bool checkPassword(std::string password);
	void sendToAll(UserPtr user, std::string command, std::string other_msg);

	void setTopic(string str);
	string getTopic(void);

		std::map<std::string, Channel::UserPtr> getAdmin(void);
		std::map<std::string, Channel::UserPtr> getUsers(void);
		std::map<std::string, Channel::UserPtr> getUsersBanned(void);
		std::map<std::string, Channel::UserPtr> getUsersInvited(void);

	public:

public:
	void printUsers(void)
	{
		map_users map = getUsers();
		map_users::iterator it = map.begin();
		map_users::iterator ite = map.end();

		while (it != ite)
		{
			std::cout << "Username : " << (*it).first << std::endl;
			std::cout << "FD : " << (*it).second->getFd() << std::endl;
			it++;
		}
	}
	//		int addUser    (UserPtr user);
	//		int removeUser (UserPtr user);
	//		int banUser    (UserPtr user);
	//		int unbanUser  (UserPtr user);
	//
	//		int isInChannel (UserPtr user);
	//		int isBanned    (UserPtr user);
	//		int isInvited   (UserPtr user);
	//
	//		void setTopic                (string str);
	//		string getTopic (void);


		void set_is_private          (bool);   // p - private channel flag;
		void set_is_secret           (bool);   // s - secret channel flag;
		void set_is_invite_only      (bool);   // i - invite-only channel flag;
		void set_is_topic_unlocked     (bool);   // t - topic settable by channel operator only flag;
		void set_is_moderated        (bool);   // m - moderated channel;
		void set_mute_non_moderators (bool);   // v - give/take the ability to speak on a moderated channel;
		void set_user_limit          (size_t); // l - set the user limit to channel;
		void set_ban_mask            (string); // b - set a ban mask to keep users out;
		void set_channel_key         (string); // k - set a channel key (password).
		void set_is_accepting_messages_from_outside_client(bool); // n - no messages to channel from clients on the outside;

		bool   get_is_private          (void); // p - private channel flag;
		bool   get_is_secret           (void); // s - secret channel flag;
		bool   get_is_invite_only      (void); // i - invite-only channel flag;
		bool   get_is_topic_unlocked     (void); // t - topic settable by channel operator only flag;
		bool   get_is_moderated        (void); // m - moderated channel;
		bool   get_mute_non_moderators (void); // v - give/take the ability to speak on a moderated channel;
		size_t get_user_limit          (void); // l - set the user limit to channel;
		string get_ban_mask            (void); // b - set a ban mask to keep users out;
		string get_channel_key         (void); // k - set a channel key (password).
		bool get_is_accepting_messages_from_outside_client(void); // n - no messages to channel from clients on the outside;

	bool does_user_exist(std::string user_name);
};
