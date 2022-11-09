/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:53 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/09 15:37:37 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Server.hpp>
#include <Channel.hpp>

/* ========================================================================== */
/* ------------------------- CONSTRUCTOR DESTRUCTOR ------------------------- */
/* ========================================================================== */

Channel::Channel(std::string ChannelName, User *channelAdmin) : _name(ChannelName), _passwd(""), _channelAdmin(channelAdmin), _invite_only(false), _passwd_required(false)
{
	addUser(channelAdmin);
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

bool Channel::is_invite_only_channel() { return _invite_only; }
bool Channel::is_password_only_channel() { return _passwd_required; }
bool Channel::checkPassword(std::string password) { return password == this->_passwd; }

void Channel::sendToAll(UserPtr user, std::string command)
{
	std::string msg = ":" + user->getNickname() + "!" + user->getHostname() + "@" + user->getIp() + " " + command + " :" + this->_name + "\r\n";
	for (map_users::iterator it = _users.begin(); it != _users.end(); it++)
	{
	send((*it).second->getFd(), msg.c_str(), msg.length(), 0);
	}
}

void Channel::addUser(UserPtr user)
{
	_users.insert(std::make_pair(user->getNickname(), user));
	sendToAll(user, "JOIN");
}
std::string Channel::getName()
{
	return (_name);
};
void Channel::removeUser(std::string nickname)
{
	(_users.erase(nickname));
}

void Channel::banUser(std::string nickname)
{
	(_users_banned.insert(std::make_pair(nickname, _users[nickname])));
}
void Channel::unbanUser(std::string nickname)
{
	(_users_banned.erase(nickname));
}

int Channel::isInChannel(std::string nickname)
{
	return (_users.find(nickname) == _users.end()) ? false : true;
}
int Channel::isBanned(std::string nickname)
{
	return (_users_banned.find(nickname) == _users_banned.end() ? false : true);
}
int Channel::isInvited(std::string nickname)
{
	return (_users_invited.find(nickname) == _users_invited.end() ? false : true);
}

void Channel::setTopic(string str) { _topic = str; }

Channel::string Channel::getTopic(void) { return _topic; }
std::map<std::string, Channel::UserPtr> Channel::getUsers(void) { return _users; }
std::map<std::string, Channel::UserPtr> Channel::getUsersBanned(void) { return _users_banned; }
std::map<std::string, Channel::UserPtr> Channel::getUsersInvited(void) { return _users_invited; }

//        ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//        ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//        ERR_CHANNELISFULL               ERR_BADCHANMASK
//        ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//        RPL_TOPIC
