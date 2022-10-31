/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 16:06:01 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) : _passwd(), _port() {}

Server::~Server(void) {}

Server::Server(std::string passwd, std::string port) : _fdServer(-1), _passwd(passwd), _port(port) {
	FD_ZERO(&(_set));

	memset(&_serverAddress, 0, sizeof(_serverAddress));
	memset(&_clientAddress, 0, sizeof(_clientAddress));
}

std::string Server::getPasswd (void) const { return (_passwd); }
std::string Server::getPort   (void) const { return (_port);   }

void Server::setPasswd (std::string pass) { _passwd = pass; }
void Server::setPort   (std::string port) { _port   = port; }

/* ...................................................... */
/* ................... NEW CONNECTION ................... */
/* ...................................................... */

int		parsing(User user) {
	(void)user;
	return (0);
}

void	generateError(User user)	{
	(void)user;
}

int Server::newConnection() {
	int fd;
	socklen_t	addrlen = sizeof(_clientAddress);
	struct epoll_event  ev;
	std::string msg = "ERROR : Server is full !\n";

	memset(&_clientAddress, 0, addrlen);
	fd = accept(_fdServer, (struct sockaddr*)&_clientAddress, &addrlen);
	if (_users.size() >= MAX_USERS) {
		send(fd, msg.c_str(), msg.length(), 0);
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
		exit(errno);
	}
	
	_users[fd] = User(fd, ip);
	return (0);
}

void	splitCmd(std::vector<std::string> & sCmd, std::string cmd) {

	size_t					pos = 0;
	std::string				delimiter = " \n\r";
	std::string::iterator	it;
	
	while ((pos = cmd.find_first_of(delimiter)) != std::string::npos)
	{
		sCmd.push_back(cmd.substr(0, pos));
		for (it = cmd.begin() + pos; it != cmd.end() && delimiter.find(*it) != std::string::npos; it++)
			pos++;
		cmd.erase(0, pos);
	}
}

void	print_buff(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	for (;it != buff.end();it++) {
		std::cout << _RED << *it << _NC << std::endl;
	}
}

void		myToupper(std::string & emma) {
	std::string::iterator	it = emma.begin();

	for (; it != emma.end();it++)
		*it = std::toupper(*it);
}

void	Server::exploreCmd(int fd, std::string buff) {
	std::vector<std::string> allBuff;
	splitCmd(allBuff, buff);
	std::vector<std::string>::iterator cmdName = allBuff.begin();
	myToupper(*cmdName);
	std::map<std::string, cmdFunc>::iterator itCmdList = _listCmd.find(*cmdName);
	const bool isValidUser= _users[fd].getValidUser(); 

	// check cmd exist
	// check cmd params error
	// Si user pas enregistrer et commande non existant air ! si enregistre command unknown
	if (itCmdList != _listCmd.end())
		itCmdList->second(this, _users[fd]);
	// execution
	if (isValidUser) {
		std::cout << _GREEN << "USER OK" << _NC << std::endl;
		std::cout << _GREEN << *cmdName << _NC << std::endl;
		std::cout << _GREEN << isValidUser << _NC << std::endl;
		//enregistrement user et error si il y a 
	
	}
	else {
		std::cout << _RED << "USER NOK" << _NC << std::endl;
		std::cout << _GREEN << *cmdName << _NC << std::endl;
		//suite de toute les autres commande sauf user et dire que deja register !
	}

}

/* ...................................................... */
/* ................... REQUEST CLIENT ................... */
/* ...................................................... */
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

	// _buffUsers[user.data.fd].append(buff);
	//Commande de test kill fd client et erase user de la map
	// if (strcmp(buff, "KILL\n") == 0) {
	// 	send(user.data.fd, "Le client doit etre kill\n", strlen("Le client doit etre kill\n"), 0);
	// 	std::map<int, User>::iterator it = _users.find(user.data.fd);
	// 	killUserClient(it->second);
	// }
	// if (strcmp(buff, "test\n") == 0) {
		// ping();
		// _listCmd
		// _listCmd[buff];
		// std::cout << _listCmd[buff] << std::endl;
	// }
	/* ...................................................... */
	/* ................... Parsing User accept ou non ! ..... */
	/* ...................................................... */
	exploreCmd(user.data.fd, buff);
	// if (!_users[user.data.fd].getValidUser()) {
		
	// }
	// else if (!parsing(_users[user.data.fd]))
			// acceptUser(_users[user.data.fd]);
	// else
	// 	generateError(_users[user.data.fd]);
	/* ...................................................... */
	/* ...................................................... */

	// _listCmd.find(buff)->second(buff);	
	// parsing a faire pour user

#if Debug
	std::cout << _BLUE << buff << _NC;
#endif

}


/* ========================================================================== */
/* ------------------------------ SERVER INIT ------------------------------- */
/* ========================================================================== */

void	Server::initCmd() {
	_listCmd["PING"] = &ping;
	_listCmd["KILL"] = &kill;
	// _listCmd["NICK"] = &nick;
}

void	Server::init(void) {
	/* .................................................. */
	/* ................. SERVER SOCKET .................. */
	/* .................................................. */
	if ((_fdServer = socket
				(
				 AF_INET,     // AF_INET == PF_INET == 2 == protocol family (IPV4)
				 SOCK_STREAM, // SOCK_STREAM means that it is a TCP socket. SOCK_DGRAM means that it is a UDP socket.
				 0            //  Specifies a particular protocol to be used with the
							  //  socket. Specifying a protocol of 0 causes socket() to
							  //  use an unspecified default protocol appropriate for
							  //  the requested socket type.
				)
		) < 0)
	{
		perror("Socket failed");
		exit(errno);
	}

	/* .................................................. */
	/* ............ SERVER SOCKET SRUCT INIT ............ */
	/* .................................................. */
	_serverAddress.sin_family      = AF_INET;                    // Address family - IPv4?
	_serverAddress.sin_addr.s_addr = INADDR_ANY;                 // 32 bit IP address  - htonl, htons, ntohl, ntohs - convert values between host and network byte or
	_serverAddress.sin_port        = htons(atoi(_port.c_str())); // 16 bit port number - htonl, htons, ntohl, ntohs - convert values between host and network byte or

	// TODO wtf is going on here
	int opt = 1; // TODO wtf is opt used for
	if (setsockopt
			(
			 _fdServer,    // Server socket
			 SOL_SOCKET,   // specifies the protocol level at which the option resides.
						   // To set options at the socket level, specify the
						   // level argument as SOL_SOCKET.
						   // TODO [?] man says to use IPPROTO_TCP for TCP
			 SO_REUSEADDR, // TODO Read this : https://stackoverflow.com/questions/3229860/what-is-the-meaning-of-so-reuseaddr-setsockopt-option-linux
						   // The option_name argument specifies a single option to set. It can
						   // be one of the socket-level options defined in sys_socket.h(0p)
						   // SO_REUSEADDR Specifies that the rules used in validating addresses supplied to bind() should allow reuse of local addresses,
						   // if this is supported by the protocol.
						   // This option takes an int value. This is a Boolean option
			 &opt,         // TODO [?] wtf (const_void * option_value)- what is the relation with SO_REUSEADDR
			 sizeof(opt)
			)
	   )
	{
		perror("Setsockopt failed");
		exit(errno);
	}

	/* .................................................. */
	/* ...................... BIND ...................... */
	/* .................................................. */
	// Bind need a general sockaddr, this is why we cast &sockaddr_in (which is spacialized) to sockaddr*
	if ((bind(_fdServer, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress))) < 0) {
		perror("Bind failed");
		exit(errno);
	}

	// Listen for socket connections and limit the queue of incoming connections
	// Second parameter (int) is the maximum number of outstanding (pending) connections
	if (listen(_fdServer, 5)) {
		perror("Listen failed");
		exit(errno);
	}
	initCmd();
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

// PING -> PONG
void	Server::cmdPing(User user, std::string hello) {
	std::string msg = PING(hello);
#if Debug
	std::cout << "CMD PING" << std::endl;
#endif
	// if (user.getFd() == user.end())
		// return ;
    if (send(user.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
		perror("Error send msg ping to client");
	}
}

void	Server::pingTime( void ) {
	double tmp;
	// std::string msg;
	std::map<const int, User>::iterator it = _users.begin(), ite = _users.end();

	for (; it != ite; it++) {
		tmp = difftime(time(NULL), it->second.getTimeActivity());
		if (tmp > PING_TIME && it->second.getPingStatus() == false) {
			cmdPing(it->second, it->second.getHostname());
			// msg = PING(it->second.getHostname());
			// if (send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
			// 	perror("Error send msg ping to client");
			// }
			it->second.setPingStatus(true);
			it->second.setTimeActivity();
		}
		else if (it->second.getPingStatus() == true) {
			// msg.clear();
			// msg = "Erreur ping TimeOut";
			tmp = difftime(time(NULL), it->second.getTimeActivity());
			if (tmp > PING_TIME) {
				cmdPing(it->second, "Erreur ping timeOut\n");
				// if (send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
				// 	perror("Error send msg ping to client");
				// }
				//kill client !
				killUserClient(it->second);
			}
		}
	} 
}

// kill user
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


	/* .................................................. */
	/* ............ EPOLL INSTANCE CREATION ............. */
	/* .................................................. */
	//  epoll_create() returns a file descriptor referring to the new epoll instance.
	//  This file descriptor is used for all the subsequent calls to  the  epoll  interface.
	//  When no longer required, the file descriptor returned by epoll_create() should be closed by using close(2).
	//  NOTE epoll_create1(0) == epoll_create()
	if ((_fdPoll = epoll_create1(0)) < 1) {
		perror("Epoll create fail");
		exit(errno);
	}

	/* .................................................. */
	/* ............ INIT EPOLL EVENT STRUCT ............. */
	/* .................................................. */
	struct epoll_event	ev;

	memset(&ev, 0, sizeof(ev)); // TODO why not bzero
	ev.events = EPOLLIN;        // == 0x001
	ev.data.fd = _fdServer;     // TODO isn't this supposed to be automatic ? check man epoll()

	// Used to add, modify, or remove entries in the interest list of the epoll(7) instance referred to by the file descriptor epfd.
	// It re‐quests that the operation op be performed for the target file descriptor, fd.
	if (epoll_ctl
			(
			 _fdPoll,          // == EPOLL fd
			 EPOLL_CTL_ADD,    // Add an entry to the interest list of the epoll file descriptor, epfd.  The entry includes the file descriptor,
							   // fd, a reference to the  corresponding open file description (see epoll(7) and open(2)),
							   // and the settings specified in event.
			 _fdServer,        // Target file descriptor
			 &ev               // Previously declared epoll_event
			) < 0
	   )
	{
		perror("Epoll_ctl fail");
		exit(errno);
	}

	/* .................................................. */
	/* ................. SERVER LAUNCH .................. */
	/* .................................................. */
	int	ready;
	struct epoll_event	user[MAX_USERS];
	while (serverLife) {          // TODO global variable which defaults to true, is this authorized ?

		if ((ready = epoll_wait   // epoll_wait returns the numbers of FDs ready for IO; 0 if none; -1 if error
					(
					 _fdPoll,     // == EPOLL fd
					 user,    // == EPOLL events TODO need explanations on events
					 MAX_USERS,   // Maximum number of events
					 0            // Specifies the number of milliseconds that epoll_wait() will block.
								  // TODO check if timeout can be set at 0
					)
			) < 0)
		{
			perror("Fail epoll wait");
			exit(errno);
		}

		for (int i = 0 ; i < ready; i++) { // TODO not sure why this is happening
			if (user[i].data.fd == _fdServer) {
				newConnection();
			}
			else {
				requestClient(user[i]);
			}
		}
		// segfault avec le ping pong !
		// revoir le msg de sortie !
		// pingTime();
	}
#if Debug
	std::cout << "Print number users : " << _GREEN << _users.size() << _NC << std::endl;
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
