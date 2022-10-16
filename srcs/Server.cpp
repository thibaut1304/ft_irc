/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/16 20:46:15 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>


Server::Server(void) : _passwd(), _port() {}

Server::~Server(void) {}

Server::Server(std::string passwd, std::string port) : _passwd(passwd), _port(port) {}

std::string	Server::getPasswd(void) const {
	return (_passwd);
}

std::string	Server::getPort(void) const {
	return (_port);
}

void	Server::setPasswd(std::string pass) {
	_passwd = pass;
}

void	Server::setPort(std::string port) {
	_port = port;
}

void	Server::launch(void) {
	const int MAX_FD = sysconf(_SC_OPEN_MAX); //necessaire pour un usage avec select
	
	while (serverLife) {
		
	}
}