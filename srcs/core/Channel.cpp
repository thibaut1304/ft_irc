/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:53 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/07 21:05:50 by adlancel         ###   ########.fr       */
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
	std::cout << "constructor" << std::endl;

	addUser(channelAdmin);
	//sendToAll(channelAdmin, "JOIN");
}

Channel::Channel(std::string ChannelName, User *channelAdmin, std::string passwd) : _name(ChannelName), _passwd(passwd), _channelAdmin(channelAdmin), _invite_only(false), _passwd_required(true)
{
	std::cout << "PASSWD CONSTRUCTOR" << std::endl;
}

Channel::Channel(Channel const &other)
{
	std::cout << "copie constructor" << std::endl;
	_name = other._name;
	_passwd = other._passwd;
	_channelAdmin = other._channelAdmin;
	_invite_only = other._invite_only;
	_passwd_required = other._passwd_required;
}
Channel::~Channel()
{
	std::cout << "destructor called" << this->_name << std::endl;
}

/* ========================================================================== */
/* ---------------------------- CHANNEL METHODS ----------------------------- */
/* ========================================================================== */

bool Channel::is_invite_only_channel() { return _invite_only; }
bool Channel::is_password_only_channel() { return _passwd_required; }
bool Channel::checkPassword(std::string password) { return password == this->_passwd; }

void Channel::sendToAll(UserPtr user, std::string command)
{
	//int i = 0;
	std::string msg;
	//map_channels::it = ch.getUsers->begin();
	Channel::map_users mu = getUsers();
	Channel::map_users::iterator it = mu.begin();
	Channel::map_users::iterator ite = mu.end();

	std::string username;
	int destination;
	while (it != ite)
	{
		username = (*it).first;
		msg = ":" + user->getNickname() + "!" + user->getHostname() + "@" + user->getIp() + " " + command + " :" + this->_name;
		destination = mu[username]->getFd();


		std::cout << "xxxxxxxxxxxxxxxxxxxx" << username<< std::endl;
		std::cout << "xxxxxxxxxxxxxxxxxxxx" << destination << std::endl;


		send(destination, msg.c_str(), msg.length(), 0);
		it++;
	}



	//while (it != ite)
	//{
		////msg = "=====================" +  (*it).first + "\n";

		//std::cout << "container size --- " << (mu.size()) << std::endl;
		//msg = ":" + user->getNickname() + "!" + user->getHostname() + "@" + user->getIp() + " " + command + " :" + this->_name;
		//std::cout << "wtf is fd " << (*it).second->getFd() << std::endl;
		//std::cout << "username is " << (*it).first<< std::endl;
		//send((*it).second->getFd(), msg.c_str(), msg.length(), 0);
		//it++;
	//}

	//for (map_users::iterator it = _users.begin(); it != _users.end(); it++)
	//{
	////std::cout << i++ << std::endl;
	//msg = "-------------------------------" + (*it).first;
	//send((*it).second->getFd(), msg.c_str(), msg.length(), 0);
	//}
}

void Channel::addUser(UserPtr user)
{
	//UserPtr user = new User(*olduser); // NOTE SUPERFIX HERE
	std::cout << "we add a user" << std::endl;
	_users.insert(std::make_pair(user->getNickname(), user));
	sendToAll(user, "JOIN");
	std::cout << "_users_size = " << _users.size() << std::endl;
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
