/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/17 10:33:16 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

Server::Server(void) : _passwd(), _port() {}

Server::~Server(void) {}

Server::Server(std::string passwd, std::string port) : _fdServer(-1), _passwd(passwd), _port(port), _nbUers(0) {
	FD_ZERO(&(_set));
	
	memset(&_serverAddress, 0, sizeof(_serverAddress));
	memset(&_clientAddress, 0, sizeof(_clientAddress));
}

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

int Server::newConnection() {
	int fd;
	socklen_t	addrlen = sizeof(_clientAddress);
	
	fd = accept(_fdServer, (struct sockaddr*)&_clientAddress, &addrlen);
	if (_nbUers >= MAX_USERS) {
		send(fd, "ERROR : server is full !\n", strlen("ERROR : server is full !\n"), 0);
		close(fd);
		return (1);
	}

	std::string ip = inet_ntoa(_clientAddress.sin_addr);
#if Debug
	std::cout << "Your IP is : " << _BLUE << ip << _NC << std::endl;
#endif
	FD_SET(fd, &(_set));
	_nbUers++;
	// _users.push_back(user(fd, ip));
	return (0);
}

void	Server::init(void) {
	int opt = 1;
	
	if ((_fdServer = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket failled");
		exit(EXIT_FAILURE);
	}
	
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(atoi(_port.c_str()));
	
	if (setsockopt(_fdServer, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("Setsockopt failled");
		exit(EXIT_FAILURE);
	}
	
	if ((bind(_fdServer, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress))) < 0) {
		perror("Bind failled");
		exit(EXIT_FAILURE);
	}
	if (listen(_fdServer, 5)) {
		perror("Listen failled");
		exit(EXIT_FAILURE);
	}
	FD_SET(_fdServer, &(_set));
}

void	Server::launch(void) {
	const int 	MAX_FD = sysconf(_SC_OPEN_MAX); //necessaire pour un usage avec select
	fd_set 		save;
	
#if Debug
	std::cout << "max fd : " << FD_SETSIZE << std::endl;
	std::cout << "max fd : " << MAX_FD << std::endl;
#endif

	while (serverLife) {
		save = _set;
		if ((select(MAX_FD + 1, &save, NULL, NULL, NULL)) < 0)
			perror("Error Select");
		for (int fdCurrent = 0 ; (fdCurrent < MAX_FD && serverLife) ; fdCurrent++)
		{
			if (FD_ISSET(fdCurrent, &save))
			{
				if (fdCurrent == _fdServer)
				{
					if (newConnection())
						continue;
				}
				// else
				// {
					// if (request_from_client(fdCurrent))
						// break;
				// }
			}
		}
	}
}