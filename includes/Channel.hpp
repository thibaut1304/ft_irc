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
		typedef std::set<UserPtr>    set_of_users;


		//typedef std::vector<UserPtr> vector_of_users;

	private:
		string          _name;
		string          _passwd;
		string          _topic;

		set_of_users    _users;
		set_of_users    _users_banned;
		set_of_users    _users_invited;

		UserPtr         _channelAdmin;

		bool            _invite_only;
		bool            _passwd_required;

		//vector_of_users _banned_users;
		//set_of_users    _invited_users;

		/* ================================================================== */
		/* ------------------------- CHANNEL FLAGS -------------------------- */
		/* ================================================================== */

		//                                                      // o - give/take channel operator privileges;
		//bool        _is_private;                                // p - private channel flag;
		//bool        _is_secret;                                 // s - secret channel flag;
		//bool        _is_invite_only;                            // i - invite-only channel flag;
		//bool        _is_topic_locked;                           // t - topic settable by channel operator only flag;
		//bool        _is_accepting_messages_from_outside_client; // n - no messages to channel from clients on the outside;
		//bool        _is_moderated;                              // m - moderated channel;
		//bool        _mute_non_moderators;                       // v - give/take the ability to speak on a moderated channel;
																////
		//size_t      _user_limit;                                // l - set the user limit to channel;
		//std::string _ban_mask;                                  // b - set a ban mask to keep users out;
		//std::string _channel_key;                               // k - set a channel key (password).



	public:

		Channel(string ChannelName, UserPtr ChannelAdmin);
		Channel(string ChannelName, UserPtr ChannelAdmin, string passwd);
		Channel(Channel const &other);
		~Channel();

		int addUser    (UserPtr user);
		int removeUser (UserPtr user);
		int banUser    (UserPtr user);
		int unbanUser  (UserPtr user);

		int isInChannel (UserPtr user);
		int isBanned    (UserPtr user);
		int isInvited   (UserPtr user);

		void   setTopic (string str);
		string getTopic (void);

		set_of_users getUsers        (void);
		set_of_users getUsersBanned  (void);
		set_of_users getUsersInvited (void);
};
