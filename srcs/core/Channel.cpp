/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:38:53 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/04 18:26:01 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>
#include <Channel.hpp>

/* ========================================================================== */
/* ------------------------- CONSTRUCTOR DESTRUCTOR ------------------------- */
/* ========================================================================== */

Channel::Channel(std::string ChannelName, int fdAdmin) : _name(ChannelName), _passwd(""), _channelAdmin(fdAdmin), _invite_only(false), _passwd_required(false)
{
	_fds.insert(fdAdmin);
}

Channel::Channel(std::string ChannelName, int fdAdmin, std::string passwd) : _name(ChannelName), _passwd(passwd), _channelAdmin(fdAdmin), _invite_only(false), _passwd_required(true)
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

int  Channel::addUser     (int fd) { return (_fds.insert(fd).second); }
int  Channel::removeUser  (int fd) { return (_fds.erase(fd));         }

int  Channel::banUser     (int fd) { return (_fds_banned.insert(fd).second); }
int  Channel::unbanUser   (int fd) { return (_fds_banned.erase(fd));         }

int  Channel::isInChannel (int fd) { return (_fds.find(fd)         == _fds.end())        ? false : true;  }
int  Channel::isBanned    (int fd) { return (_fds_banned.find(fd)  == _fds_banned.end()  ? false : true); }
int  Channel::isInvited   (int fd) { return (_fds_invited.find(fd) == _fds_invited.end() ? false : true); }

void Channel::setTopic    (string  str)  { _topic = str; }

Channel::string     Channel::getTopic        (void) { return _topic;       }
Channel::set_of_fds Channel::getUsers        (void) { return _fds;         }
Channel::set_of_fds Channel::getUsersBanned  (void) { return _fds_banned;  }
Channel::set_of_fds Channel::getUsersInvited (void) { return _fds_invited; }

//        ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//        ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//        ERR_CHANNELISFULL               ERR_BADCHANMASK
//        ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//        RPL_TOPIC
