/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:53 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/18 11:20:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>
#include <Channel.hpp>

/* ========================================================================== */
/* ------------------------- CONSTRUCTOR DESTRUCTOR ------------------------- */
/* ========================================================================== */

Channel::Channel(std::string ChannelName, User *channelAdmin) :
	_name                (ChannelName),
	_passwd              (""),
	_nbUsers			 (0),
	_passwd_required     (false),
	_is_private          (false),
	_is_secret           (false),
	_is_invite_only      (false),
	_is_topic_unlocked   (true),
	_is_moderated        (false),
	_mute_non_moderators (false),
	_user_limit          (0),
	_channel_key         (""),
	_is_accepting_messages_from_outside_client (true),
	_users_banned         ()
{
	_channelAdmin.insert(std::make_pair(channelAdmin->getNickname(), channelAdmin));
	addUser(channelAdmin);
}

Channel::Channel(Channel const &other)
{
	_nbUsers             = other._nbUsers;
	_name                = other._name;
	_passwd              = other._passwd;
	_channelAdmin        = other._channelAdmin;
	_passwd_required     = other._passwd_required;
	_is_private          = other._is_private;
	_is_secret           = other._is_secret;
	_is_invite_only      = other._is_invite_only;
	_is_topic_unlocked   = other._is_topic_unlocked;
	_is_moderated        = other._is_moderated;
	_mute_non_moderators = other._mute_non_moderators;
	_user_limit          = other._user_limit;
	_users_banned        = other._users_banned;
	_channel_key         = other._channel_key;
	_is_accepting_messages_from_outside_client = other._is_accepting_messages_from_outside_client;
}

Channel::~Channel()
{
}

/* ========================================================================== */
/* -------------------------------- SETTERS --------------------------------- */
/* ========================================================================== */

void Channel::set_is_private          (bool b)          { _is_private          = b; }   // p - private channel flag;
void Channel::set_is_secret           (bool b)          { _is_secret           = b; }   // s - secret channel flag;
void Channel::set_is_invite_only      (bool b)          { _is_invite_only      = b; }   // i - invite-only channel flag;
void Channel::set_is_topic_unlocked   (bool b)          { _is_topic_unlocked   = b; }   // t - topic settable by channel operator only flag;
void Channel::set_is_moderated        (bool b)          { _is_moderated        = b; }   // m - moderated channel;
void Channel::set_mute_non_moderators (bool b)          { _mute_non_moderators = b; }   // v - give/take the ability to speak on a moderated channel;
void Channel::set_user_limit          (size_t s)        { _user_limit          = s; } // l - set the user limit to channel;
void Channel::set_channel_key         (string str)      { _channel_key         = str; _passwd_required = true; }; // k - set a channel key (password).
void Channel::setTopic                (string str)      { _topic = str; }
void Channel::set_is_accepting_messages_from_outside_client(bool b) {_is_accepting_messages_from_outside_client = b;} //// n - no messages to channel from clients on the outside;

/* ========================================================================== */
/* -------------------------------- GETTERS --------------------------------- */
/* ========================================================================== */

bool        Channel::get_is_private           (void) { return _is_private          ; }// p - private channel flag;
bool        Channel::get_is_secret            (void) { return _is_secret           ; }// s - secret channel flag;
bool        Channel::get_is_invite_only       (void) { return _is_invite_only      ; }// i - invite-only channel flag;
bool        Channel::get_is_topic_unlocked    (void) { return _is_topic_unlocked   ; }// t - topic settable by channel operator only flag;
bool        Channel::get_is_moderated         (void) { return _is_moderated        ; }// m - moderated channel;
bool        Channel::get_mute_non_moderators  (void) { return _mute_non_moderators ; }// v - give/take the ability to speak on a moderated channel;
bool        Channel::is_invite_only_channel   (void) { return _is_invite_only      ; }
bool        Channel::is_password_only_channel (void) { return _passwd_required     ; }
int         Channel::numberOfUsers            (void) { return _nbUsers             ; }
size_t      Channel::get_user_limit           (void) { return _user_limit          ; }// l - set the user limit to channel;
size_t      Channel::getSize                  (void) { return _nbUsers             ; }
std::string Channel::get_channel_key          (void) { return _channel_key         ; }// k - set a channel key (password).
std::string Channel::getTopic                 (void) { return _topic               ; }
std::string Channel::getName                  (void) { return _name                ; }

bool Channel::get_is_accepting_messages_from_outside_client (void) {return _is_accepting_messages_from_outside_client;}

/* CHANNEL USERS .................... */
/* .................................. */
Channel::vector_banned_users            Channel::getUsersBanned  (void) { return _users_banned;  }
Channel::vector_banned_users&           Channel::get_banned_users(void) { return _users_banned;  }
std::map<std::string,Channel::UserPtr>  Channel::getAdmin        (void) { return _channelAdmin;  }
std::map<std::string,Channel::UserPtr>  Channel::getUsers        (void) { return _users;         }
std::map<std::string,Channel::UserPtr>& Channel::getUsersRef     (void) { return _users;         }
std::map<std::string,Channel::UserPtr>  Channel::getUsersInvited (void) { return _users_invited; }

 /* USER STATES ..................... */
 /* ................................. */
int Channel::isAdmin    (std::string nickname) { return (_channelAdmin.find(nickname)  == _channelAdmin.end()  ? false : true); }
int Channel::isInvited  (std::string nickname) { return (_users_invited.find(nickname) == _users_invited.end() ? false : true); }
int Channel::isInChannel(std::string nickname) { return (_users.find(nickname)         == _users.end()) ? false : true;         }

bool Channel::checkPassword (string password) { return password == this->_channel_key; }

/* ========================================================================== */
/* ---------------------------- CHANNEL METHODS ----------------------------- */
/* ========================================================================== */


/* COMMUNICATION .................... */
/* .................................. */
void Channel::sendToAll(UserPtr user, std::string command, std::string other_msg )
{
	std::string msg = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getIp() + " ";

	if (other_msg == "")
		msg += command + " :" + this->_name + "\r\n";
	else
		msg += command + " " + this->_name + " :" + other_msg + "\r\n";

	for (map_users::iterator it = _users.begin(); it != _users.end(); it++)
		send(it->second->getFd(), msg.c_str(), msg.length(), 0);
}

/* USER ADD ......................... */
/* .................................. */

void Channel::addAdmin (UserPtr user) { _channelAdmin.insert(std::make_pair(user->getNickname(), user)); }
void Channel::addUser  (UserPtr user)
{
	_users.insert(std::make_pair(user->getNickname(), user));
	sendToAll(user, "JOIN");
	_nbUsers++;
}

void Channel::unbanUser(std::string nickname)
{
	vector_banned_users::iterator it  = _users_banned.begin();
	vector_banned_users::iterator ite =  _users_banned.end();
	while (it != ite)
	{
		if (*it == nickname)
			break;
		it++;
	}
	if (it != ite)
		_users_banned.erase(it);
}

/* USER REMOVE ...................... */
/* .................................. */
void Channel::removeAdmin (std::string nick)     { _channelAdmin.erase(nick);         }
void Channel::banUser     (std::string nickname) { _users_banned.push_back(nickname); }

void Channel::removeUser(UserPtr user)
{
	sendToAll(user, "PART");
	(_users.erase(user->getNickname()));
	_nbUsers--;
}

/* USER INVITE ...................... */
/* .................................. */
void Channel::inviteUser(UserPtr user)
{
	_users_invited.insert(std::make_pair(user->getNickname(), user));
	for (std::map<std::string, UserPtr>::iterator it = _users_invited.begin(); it != _users_invited.end(); it++)
	{
		if (Debug)
			std::cout << "user invited : " << it->second->getNickname() << std::endl;
	}
}

/* USER QUERIES ..................... */
/* .................................. */

int Channel::isBanned(std::string nickname)
{
	vector_banned_users::iterator it  = _users_banned.begin();
	vector_banned_users::iterator ite =  _users_banned.end();
	while (it != ite)
	{
		if (*it == nickname)
			break;
		it++;
	}
	if (it != ite)
		return true;
	return false;
}


bool Channel::does_user_exist(std::string user_name)
{
	map_users users = getUsers();
	map_users::iterator it = users.begin();
	map_users::iterator ite = users.end();
	while (it != ite)
	{
		if (user_name == it->second->getNickname())
			return (true);
		it++;
	}
	return (false);
}
