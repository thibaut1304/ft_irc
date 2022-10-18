/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:38:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/18 18:25:21 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Users.hpp>

User::User( void ) : _fd(0) {}

User::User( const int fd, std::string hostname ) : _fd(fd), _hostname(hostname), _nickname(""), _username(""), _fullname("") {}

User::User(const User &rhs) : _fd(rhs._fd), _hostname(rhs._hostname), _nickname(rhs._nickname), _username(rhs._username), _fullname(rhs._fullname) {}

User &User::operator=(const User &rhs) {
	if (this != &rhs) {
		_hostname = rhs._hostname;
		_nickname = rhs._nickname;
		_username = rhs._username;
		_fullname = rhs._fullname;
	}
	return (*this);
}

User::~User() {}

int		User::getFd() const {
	return (_fd);
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