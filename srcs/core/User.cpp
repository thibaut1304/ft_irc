/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:38:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/11 06:47:17 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Users.hpp>

User::User( void ) : _fd(0) {}

User::User( const int fd, const std::string hostname ) \
	: _fd                    (fd)
	, _time(time             (NULL))
	, _statusPing            (false)
	, _validUser             (false)
	, _receive_wallops       (true)
	, _receive_server_notice (true)
	, _is_invisible          (false)
	, _is_operator           (false)
	, _ip                    (hostname)
	, _hostname              ("")
	, _nickname              ("")
	, _username              ("")
	, _fullname              ("")
	, _PASS                  ("")
	, _isKill                (false)
{
}

User::User(const User &rhs) \
	: _fd				     (rhs._fd)
	, _time			         (rhs._time)
	, _statusPing	         (rhs._statusPing)
	, _validUser	         (rhs._validUser)
	, _receive_wallops       (rhs._receive_wallops)
	, _receive_server_notice (rhs._receive_server_notice)
	, _is_invisible          (rhs._is_invisible)
	, _is_operator           (rhs._is_operator)
	, _ip					 (rhs._ip)
	, _hostname				 (rhs._hostname)
	, _nickname				 (rhs._nickname)
	, _username				 (rhs._username)
	, _fullname				 (rhs._fullname)
	, _PASS					 (rhs._PASS)
	, _isKill				 (rhs._isKill)
{
}

User &User::operator=(const User &rhs) {
	if (this != &rhs) {
		_time                  = rhs._time;
		_fd                    = rhs._fd;
		_ip                    = rhs._ip;
		_hostname              = rhs._hostname;
		_nickname              = rhs._nickname;
		_username              = rhs._username;
		_fullname              = rhs._fullname;
		_PASS                  = rhs._PASS;
		_statusPing            = rhs._statusPing;
		_validUser             = rhs._validUser;
		_isKill                = rhs._isKill;
		_receive_wallops       = rhs._receive_wallops;
		_receive_server_notice = rhs._receive_server_notice;
		_is_invisible          = rhs._is_invisible;
		_is_operator           = rhs._is_operator;
	}
	return (*this);
}

User::~User() {
	//delete this;
	//std::cout<< "Destroyed : " << _nickname << std::endl;
}

int         User::getFd                     (void) const { return (_fd);                    }
time_t      User::getTimeActivity           (void) const { return (_time);                  }
bool        User::getPingStatus             (void) const { return (_statusPing);            }
bool        User::getValidUser              (void) const { return (_validUser);             }
std::string User::getNickname               (void) const { return (_nickname);              }
std::string User::getUsername               (void) const { return (_username);              }
std::string User::getFullName               (void) const { return (_fullname);              }
std::string User::getHostname               (void) const { return (_hostname);              }
std::string User::getIp                     (void) const { return (_ip);                    }
std::string User::getPASS                   (void) const { return (_PASS);                  }
bool        User::getIsKill                 (void) const { return (_isKill);                }
bool        User::get_receive_wallops       (void) const { return (_receive_wallops);       }
bool        User::get_receive_server_notice (void) const { return (_receive_server_notice); }
bool        User::get_is_invisible          (void) const { return (_is_invisible);          }
bool        User::get_is_operator           (void) const { return (_is_operator);           }

void	User::setTimeActivity	(void)					{ _time 		= time(NULL);	}
void	User::setPingStatus		(bool ret)				{ _statusPing 	= ret;  		}
void	User::setValidUser		(bool ret) 				{ _validUser  	= ret;  		}
void	User::setNickname		(std::string nick)		{ _nickname   	= nick; 		}
void	User::setUsername		(std::string username)	{ _username   	= username;		}
void	User::setFullName		(std::string fullName)	{ _fullname   	= fullName;		}
void	User::setHostname		(std::string hostname)	{ _hostname   	= hostname; 	}
void	User::setIsKill		  	(bool kill) 			{ _isKill 		= kill;			}
void 	User::setPASS			(std::string pass)		{ _PASS			= pass;			}

void User::set_receive_wallops       (bool b) { _receive_wallops      = b; }
void User::set_receive_server_notice (bool b) { _receive_server_notice = b; }
void User::set_is_invisible          (bool b) { _is_invisible         = b; }
void User::set_is_operator           (bool b) { _is_operator          = b; }





