/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:53 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/04 20:45:09 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Channel.hpp>

/* ========================================================================== */
/* ------------------------- CONSTRUCTOR DESTRUCTOR ------------------------- */
/* ========================================================================== */

Channel::Channel(std::string ChannelName, User *channelAdmin) : _name(ChannelName), _passwd(""), _channelAdmin(channelAdmin), _invite_only(false), _passwd_required(false)
{
	_users.insert(channelAdmin);
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

/* ========================================================================== */
/* ---------------------------- CHANNEL METHODS ----------------------------- */
/* ========================================================================== */

int  Channel::addUser     (UserPtr user) { return (_users.insert(user).second); }
int  Channel::removeUser  (UserPtr user) { return (_users.erase(user));         }

int  Channel::banUser     (UserPtr user) { return (_users_banned.insert(user).second); }
int  Channel::unbanUser   (UserPtr user) { return (_users_banned.erase(user));         }

int  Channel::isInChannel (UserPtr user) { return (_users.find(user)         == _users.end())        ? false : true;  }
int  Channel::isBanned    (UserPtr user) { return (_users_banned.find(user)  == _users_banned.end()  ? false : true); }
int  Channel::isInvited   (UserPtr user) { return (_users_invited.find(user) == _users_invited.end() ? false : true); }

void Channel::setTopic    (string  str)  { _topic = str; }

Channel::string       Channel::getTopic        (void) { return _topic;         }
Channel::set_of_users Channel::getUsers        (void) { return _users;         }
Channel::set_of_users Channel::getUsersBanned  (void) { return _users_banned;  }
Channel::set_of_users Channel::getUsersInvited (void) { return _users_invited; }

//        ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//        ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//        ERR_CHANNELISFULL               ERR_BADCHANMASK
//        ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//        RPL_TOPIC
