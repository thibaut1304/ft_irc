/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/02 16:37:14 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <netinet/in.h>

/* ========================================================================== */
/* ----------------------- CONSTRUCTORS / DESTRUCTOR ------------------------ */
/* ========================================================================== */

// NOTE TODO @thibault added _fdServer(-1) to default constructor, please check if ok
Server::Server(void)                                 : _fdServer(-1), _passwd(),       _port()     {}
Server::Server(std::string passwd, std::string port) : _fdServer(-1), _passwd(passwd), _port(port) {
	FD_ZERO(&(_set));

	memset(&_serverAddress, 0, sizeof(_serverAddress));
	memset(&_clientAddress, 0, sizeof(_clientAddress));
}
Server::~Server(void) {}

std::string Server::getPasswd (void) const       { return (_passwd); }
std::string Server::getPort   (void) const       { return (_port);   }
void        Server::setPasswd (std::string pass) { _passwd = pass;   }
void        Server::setPort   (std::string port) { _port   = port;   }

/* ========================================================================== */
/* ------------------------------ SERVER INIT ------------------------------- */
/* ========================================================================== */


void	Server::init(void) {
	server_init_socket_fd         (&_fdServer);
	server_init_socket_struct     (_fdServer, _serverAddress, _port);
	server_init_bind_fd_to_socket (_fdServer, _serverAddress);
	server_init_check             (_fdServer);
	initCmd(); // NOTE this is a Server::method
}

/* ========================================================================== */
/* ----------------------------- SERVER LAUNCH ------------------------------ */
/* ========================================================================== */

void	Server::launch(void) {
	// const int 			MAX_FD = sysconf(_SC_OPEN_MAX); //necessaire pour un usage avec select

	// NOTE: The  epoll  API  performs  a similar task to poll(2):
	// monitoring multiple file descriptors to see if I/O is possible on any of them.
	// The central concept of the epoll API is the epoll instance,
	// an in-kernel data structure which, from a user-space perspective,
	// considered as a container for two lists:
	//     uint32_t     events - interest list (== epoll set), is a list of fd that the process "wants" to monitor
	//     epoll_data_t data   - ready    list , list of fds which are ready for IO

	server_launch_epoll_init        (_fdPoll);
	server_launch_epoll_struct_init (_fdServer, _fdPoll);
	server_launch_start             (_fdServer, _fdPoll, *this);
}

/* ========================================================================== */
/* ----------------------------- NEW CONNECTION ----------------------------- */
/* ========================================================================== */

int Server::newConnection() {
	int         fdNew;
	std::string ip;

	fdNew = server_new_connection_accept(_fdServer, _clientAddress, _users.size());
	if (fdNew == -1)
		return (1);
	ip    = inet_ntoa(_clientAddress.sin_addr);
	__debug_newConnection(ip);
	server_new_connection_epoll_ctl(fdNew, _fdPoll);
	_users[fdNew] = User(fdNew, ip);
	return (0);
}

/* ========================================================================== */
/* ----------------------------- REQUEST CLIENT ----------------------------- */
/* ========================================================================== */

void	Server::requestClient(struct epoll_event user) {
	char			buff[BUFF_SIZE];
	int 			ret;
	std::string		msg;

	memset(buff, 0, BUFF_SIZE);
	if ((ret = recv(user.data.fd, buff, BUFF_SIZE, 0)) < 0) {
		perror("Fail recv user");
		exit(errno);
	}
	buff[ret] = 0;
	_buffUsers[user.data.fd].append(buff);
	// std::cout << _YELLOW << _buffUsers[user.data.fd] << _NC << std::endl;
	exploreCmd(user.data.fd, buff);
	__debug_requestClient(buff);
}

/* ========================================================================== */
/* ---------------------------- KILL USER CLIENT ---------------------------- */
/* ========================================================================== */

void	Server::killUserClient( User user ) {
	std::cout << "CMD killUserClient\n";
	int fd = user.getFd();

	if (epoll_ctl(_fdPoll, EPOLL_CTL_DEL, fd, NULL) < 0) {
		perror("Error epoll ctl del client");
		exit(EXIT_FAILURE);
	}
	if (close(fd) < 0) {
		perror("Error close fd client");
		exit(EXIT_FAILURE);
	}
	_users.erase(fd);
}

/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */
/* ------------------------- TODO WORK IN PROGRESS -------------------------- */
/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

int		parsing      (User user) { (void)user; return (0); }
void	generateError(User user) { (void)user; }

void	Server::initCmd() {
	_listCmd["PING"] = &ping;
	_listCmd["KILL"] = &kill;
	_listCmd["NICK"] = &nick;
	_listCmd["USER"] = &user;
	_listCmd["CAP"]  = &cap;
	_listCmd["PASS"] = &pass;
	
}

void	Server::exploreCmd(int fd, std::string buff) {
	// int i = 0;
	// while (buff.c_str()[i]) {
		// if (std::isspace(buff.c_str()[i]))
			// i++;
	// }
	// if (!buff.c_str()[i]) {
		// std::cout << "RETURN" << std::endl;
		// exit(1) ;
	// }
	if (buff.size() == 0)
		return ;
	_buff = buff;
	(void)fd;
	std::vector<std::string> tmp;
	splitCmdIrssi(tmp, buff);
	// print_buff(tmp);
	std::vector<std::string>::iterator it_tmp = tmp.begin();
		std::cout << *it_tmp <<  std::endl;
	for (;it_tmp != tmp.end(); it_tmp++) {
		_allBuff.clear();
		splitCmd(_allBuff, *it_tmp);
		print_buff(_allBuff);
		// std::cout << std::endl;
		// std::cout << std::endl;
		
		std::vector<std::string>::iterator cmdName = _allBuff.begin();
		myToupper(*cmdName);
		// std::cout << _YELLOW << "|" << *cmdName << "|" << _NC << std::endl;
		std::map<std::string, cmdFunc>::iterator itCmdList = _listCmd.find(*cmdName);
		// check cmd exist
		// check cmd params error
		// Si user pas enregistrer et commande non existant air ! si enregistre command unknown
		std::cout << _YELLOW << "|-|" << *cmdName << "|-|" << _NC << std::endl;
		if (itCmdList == _listCmd.end() && _users[fd].getValidUser() == false) {
			return ;
		}
		else if (itCmdList == _listCmd.end()) {
			std::string msg = NAME + ERR_UNKNOWNCOMMAND(_users[fd].getNickname(), print_cmd(_allBuff));
			send(_users[fd].getFd(), msg.c_str(), msg.length(), 0);
		}
		else {
	#if DEBUG
		std::cout << _CYAN << "CMD FIND" << _NC << std::endl;
	#endif
			itCmdList->second(this, _users[fd]);
		}

		if (!_users[fd].getValidUser()				
			&& !_users[fd].getNickname().empty() 	
			&& !_users[fd].getUsername().empty()	
			&& !_users[fd].getFullName().empty()	
			&& !_users[fd].getHostname().empty())	{
			_users[fd].setValidUser(true);
			acceptUser(_users[fd]);
		}
		const bool isValidUser = _users[fd].getValidUser();

		// std::cout << _YELLOW << _users[fd].getNickname() << _NC <<std::endl;
		// execution
		if (isValidUser) {
			std::cout << _GREEN << "USER OK" << _NC << std::endl;
		}
		else {
			std::cout << _RED << "USER NOK" << _NC << std::endl;
		}
	// 	_buffUsers[fd].clear();
		_allBuff.clear();
	}
}

// void	Server::cmdPing(User user, std::string hello) {
// 	std::string msg = PING(hello);
// 	__debug_exploreCmd();
// 	// if (user.getFd() == user.end())
// 	// return ;
// 	if (send(user.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
// 		perror("Error send msg ping to client");
// 	}
// }

// void	Server::pingTime( void ) {
// 	double tmp;
// 	// std::string msg;
// 	std::map<const int, User>::iterator it = _users.begin(), ite = _users.end();

// 	for (; it != ite; it++) {
// 		tmp = difftime(time(NULL), it->second.getTimeActivity());
// 		if (tmp > PING_TIME && it->second.getPingStatus() == false) {
// 			cmdPing(it->second, it->second.getHostname());
// 			// msg = PING(it->second.getHostname());
// 			// if (send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
// 			// 	perror("Error send msg ping to client");
// 			// }
// 			it->second.setPingStatus(true);
// 			it->second.setTimeActivity();
// 		}
// 		else if (it->second.getPingStatus() == true) {
// 			// msg.clear();
// 			// msg = "Erreur ping TimeOut";
// 			tmp = difftime(time(NULL), it->second.getTimeActivity());
// 			if (tmp > PING_TIME) {
// 				cmdPing(it->second, "Erreur ping timeOut\n");
// 				// if (send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
// 				// 	perror("Error send msg ping to client");
// 				// }
// 				//kill client !
// 				killUserClient(it->second);
// 			}
// 		}
// 	}
// }
