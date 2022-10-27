/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/24 14:19:20 by thhusser         ###   ########.fr       */
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
		exit(errno);
	}
	_users[fd] = User(fd, ip);
	// _users.push_back(user(fd, ip));
	return (0);
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

	_buffUsers[user.data.fd].append(buff);

	// parsing a faire pour user

#if Debug
	std::cout << _BLUE << buff << _NC;
#endif

}


/* ========================================================================== */
/* ------------------------------ SERVER INIT ------------------------------- */
/* ========================================================================== */

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

	// FD_SET(_fdServer, &(_set));
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
	struct epoll_event	*user_tmp;
	struct epoll_event	user[MAX_USERS];
	while (serverLife) {          // TODO global variable which defaults to true, is this authorized ?
		user_tmp = &(user[0]);    // TODO user was never initialized, how does this work ?

		if ((ready = epoll_wait   // epoll_wait returns the numbers of FDs ready for IO; 0 if none; -1 if error
					(
					 _fdPoll,     // == EPOLL fd
					 user_tmp,    // == EPOLL events TODO need explanations on events
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
