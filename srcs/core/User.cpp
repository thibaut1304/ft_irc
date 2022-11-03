/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:38:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/03 21:06:19 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Users.hpp>

User::User( void ) : _fd(0) {}

User::User( const int fd, const std::string hostname ) :
	_fd           (fd)
	, _time(time  (NULL))
	, _statusPing (false)
	, _validUser  (false)
	, _ip   	  (hostname)
	, _hostname   ("")
	, _nickname   ("")
	, _username   ("")
	, _fullname   ("")
{
	std::cout << "creation USER fd : " << fd << std::endl;
}

User::User(const User &rhs) :
	_fd				(rhs._fd)
	, _time			(rhs._time)
	, _statusPing	(rhs._statusPing)
	, _validUser	(rhs._validUser)
	, _ip			(rhs._ip)
	, _hostname		(rhs._hostname)
	, _nickname		(rhs._nickname)
	, _username		(rhs._username)
	, _fullname		(rhs._fullname)
{}

User &User::operator=(const User &rhs) {
	if (this != &rhs) {
		_time       = rhs._time;
		_fd         = rhs._fd;
		_ip 		= rhs._ip;
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
std::string User::getIp			  (void) const { return (_ip);		   }

void	User::setTimeActivity	(void)					{ _time 		= time(NULL);	}
void	User::setPingStatus		(bool ret)				{ _statusPing 	= ret;  		}
void	User::setValidUser		(bool ret) 				{ _validUser  	= ret;  		}
void	User::setNickname		(std::string nick)		{ _nickname   	= nick; 		}
void	User::setUsername		(std::string username)	{ _username   	= username;		}
void	User::setFullName		(std::string fullName)	{ _fullname   	= fullName;		}
void	User::setHostname		(std::string hostname)	{ _hostname   	= hostname; 	}
