/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:38:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 13:57:19 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Users.hpp>

User::User( void ) : _fd(0) {}

User::User( const int fd, const std::string hostname ) : _fd(fd), _time(time(NULL)), _statusPing(false), _validUser(false),  _hostname(hostname), _nickname(""), _username(""), _fullname("") {
	std::cout << "creation USER fd : " << fd << std::endl;
}

User::User(const User &rhs) : _fd(rhs._fd), _time(rhs._time),_statusPing(rhs._statusPing), _validUser(rhs._validUser), _hostname(rhs._hostname), _nickname(rhs._nickname), _username(rhs._username), _fullname(rhs._fullname) {}

User &User::operator=(const User &rhs) {
	if (this != &rhs) {
		_time = rhs._time;
		_fd = rhs._fd;
		_hostname = rhs._hostname;
		_nickname = rhs._nickname;
		_username = rhs._username;
		_fullname = rhs._fullname;
		_statusPing = rhs._statusPing;
		_validUser = rhs._validUser;
	}
	return (*this);
}

User::~User() {}

int		User::getFd() const {
	return (_fd);
}	

time_t	User::getTimeActivity() const {
	return (_time);
}

bool	User::getPingStatus() const {
	return (_statusPing);
}

bool	User::getValidUser() const {
	return (_validUser);
}

std::string	User::getNickname() const {
	return (_nickname);
}

std::string	User::getUsername() const {
	return (_username);
}

std::string	User::getFullName() const {
	return (_fullname);
}

std::string	User::getHostname() const {
	return (_hostname);
}

void	User::setTimeActivity() {
	_time = time(NULL);
}

void	User::setPingStatus(bool ret) {
	_statusPing = ret;
}

void	User::setValidUser(bool ret) {
	_validUser = ret;
}