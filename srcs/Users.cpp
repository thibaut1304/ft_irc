/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:38:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 14:48:14 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Users.hpp>

User::User( void ) : _fd(0) {}

User::User( const int fd, const std::string hostname ) :
	_fd           (fd)
	, _time(time  (NULL))
	, _statusPing (false)
	, _validUser  (false)
	, _hostname   (hostname)
	, _nickname   ("")
	, _username   ("")
	, _fullname   ("")
{
	std::cout << "creation USER fd : " << fd << std::endl;
}

User::User(const User &rhs) :
	_fd           (rhs._fd)
	, _time       (rhs._time)
	, _statusPing (rhs._statusPing)
	, _validUser  (rhs._validUser)
	, _hostname   (rhs._hostname)
	, _nickname   (rhs._nickname)
	, _username   (rhs._username)
	, _fullname   (rhs._fullname)
{}

User &User::operator=(const User &rhs) {
	if (this != &rhs) {
		_time       = rhs._time;
		_fd         = rhs._fd;
		_hostname   = rhs._hostname;
		_nickname   = rhs._nickname;
		_username   = rhs._username;
		_fullname   = rhs._fullname;
		_statusPing = rhs._statusPing;
		_validUser  = rhs._validUser;
	}
	return (*this);
}

User::~User() {}

int         User::getFd           (void) const { return (_fd);         }
time_t      User::getTimeActivity (void) const { return (_time);       }
bool        User::getPingStatus   (void) const { return (_statusPing); }
bool        User::getValidUser    (void) const { return (_validUser);  }
std::string User::getNickname     (void) const { return (_nickname);   }
std::string User::getUsername     (void) const { return (_username);   }
std::string User::getFullName     (void) const { return (_fullname);   }
std::string User::getHostname     (void) const { return (_hostname);   }

void	User::setTimeActivity	(void)				{ _time = time(NULL); }
void	User::setPingStatus		(bool ret)			{ _statusPing = ret;  }
void	User::setValidUser		(bool ret) 			{ _validUser  = ret;  }
void	User::setNickname		(std::string nick)	{ _nickname   = nick; }