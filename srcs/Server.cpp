/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/18 18:26:52 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

Server::Server(void) : _passwd(), _port() {}

Server::~Server(void) {}

Server::Server(std::string passwd, std::string port) : _fdServer(-1), _passwd(passwd), _port(port) {
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
    struct epoll_event  ev;
	
	memset(&_clientAddress, 0, addrlen);
	fd = accept(_fdServer, (struct sockaddr*)&_clientAddress, &addrlen);
	if (_users.size() >= MAX_USERS) {
		send(fd, "ERROR : Server is full !\n", strlen("ERROR : Server is full !\n"), 0);
		close(fd);
		return (1);
	}

	std::string ip = inet_ntoa(_clientAddress.sin_addr);
#if Debug
	std::cout << "Your IP is : " << _BLUE << ip << _NC << std::endl;
#endif
	memset(&ev, 0, sizeof(struct epoll_event));
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;
	if (epoll_ctl(_fdPoll, EPOLL_CTL_ADD, fd, &ev) < 0) {
		perror("Epoll ctl User fail");
		exit(EXIT_FAILURE);
	}
	_users[fd] = User(fd, ip);
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

// typedef union epoll_data {
//     void *ptr;
//     int fd;
//     __uint32_t u32;
//     __uint64_t u64;
// } epoll_data_t;

// struct epoll_event {
//     __uint32_t events;    /* Événement epoll      */
//     epoll_data_t data;    /* Variable utilisateur */
// };

void	Server::launch(void) {
	// const int 			MAX_FD = sysconf(_SC_OPEN_MAX); //necessaire pour un usage avec select
	int					ready;
	struct epoll_event	ev;
	struct epoll_event	user[MAX_USERS];
	struct epoll_event	*user_tmp;

	memset(&ev, 0, sizeof(ev));
	if ((_fdPoll = epoll_create1(0)) < 1) {
		perror("Epoll create fail");
		exit(EXIT_FAILURE);
	}
	ev.events = EPOLLIN;
	ev.data.fd = _fdServer;
	if (epoll_ctl(_fdPoll, EPOLL_CTL_ADD, _fdServer, &ev) < 0) {
		perror("Epoll_ctl fail");
		exit(EXIT_FAILURE);
	}
	while (serverLife) {
		user_tmp = &(user[0]);
		if ((ready = epoll_wait(_fdPoll, user, MAX_USERS, 0)) < 0) { // vois si le timeout on peut le mettre a 0
			perror("Fail epoll wait");
			exit(EXIT_FAILURE);
			}
		for (int i = 0 ; i < ready; i++) {
			if (user[i].data.fd == _fdServer) {
				newConnection();
			}
		}
	}
#if Debug
	std::cout << _GREEN << "Print number users : " << _users.size() << _NC << std::endl;
	typedef std::map<const int, User>::iterator it;
	for (it e = _users.begin() ; e != _users.end(); e++) {
		std::cout << "FD : " << _YELLOW << e->first << _NC;
		if (e != --_users.end())
			std::cout << ", ";
		else
			std::cout << ".\n";
	}
	
#endif
}