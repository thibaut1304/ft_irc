/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:55:51 by wszurkow          #+#    #+#             */
/*   Updated: 2022/10/31 17:56:56 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void server_init_socket_fd(int *fd)
{
	if ((*fd = socket
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
}

void server_init_socket_struct(int fd, sockaddr_in & server_sock_struct, std::string port)
{
	server_sock_struct.sin_family      = AF_INET;                    // Address family - IPv4?
	server_sock_struct.sin_addr.s_addr = INADDR_ANY;                 // 32 bit IP address  - htonl, htons, ntohl, ntohs - convert values between host and network byte or
	server_sock_struct.sin_port        = htons(atoi(port.c_str())); // 16 bit port number - htonl, htons, ntohl, ntohs - convert values between host and network byte or

	// TODO wtf is going on here
	int opt = 1; // TODO wtf is opt used for
	if (setsockopt
			(
			 fd,           // Server socket
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
}

void server_init_bind_fd_to_socket(int fd, sockaddr_in & server_sock_struct)
{
	// Bind need a general sockaddr, this is why we cast &sockaddr_in (which is spacialized) to sockaddr*
	if ((bind(fd, (struct sockaddr *)&server_sock_struct, sizeof(server_sock_struct))) < 0) {
		perror("Bind failed");
		exit(errno);
	}
}

void server_init_check(int fd)
{
	// Listen for socket connections and limit the queue of incoming connections
	// Second parameter (int) is the maximum number of outstanding (pending) connections
	if (listen(fd, 5)) {
		perror("Listen failed");
		exit(errno);
	}
}

