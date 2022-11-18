/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_launch.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:23:04 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 20:53:42 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void server_launch_epoll_init(int & fdPoll)
{
	//  epoll_create() returns a file descriptor referring to the new epoll instance.
	//  This file descriptor is used for all the subsequent calls to  the  epoll  interface.
	//  When no longer required, the file descriptor returned by epoll_create() should be closed by using close(2).
	//  NOTE epoll_create1(0) == epoll_create()

	if ((fdPoll = epoll_create1(0)) < 1) {
		perror("Epoll create fail");
		exit(errno);
	}
}
void server_launch_epoll_struct_init(int fdServer, int fdPoll)
{
	struct epoll_event	ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;        // == 0x001
	ev.data.fd = fdServer;

	// Used to add, modify, or remove entries in the interest list of the epoll(7) instance referred to by the file descriptor epfd.
	// It re‐quests that the operation op be performed for the target file descriptor, fd.
	if (epoll_ctl
			(
			 fdPoll,          // == EPOLL fd
			 EPOLL_CTL_ADD,   // Add an entry to the interest list of the epoll file descriptor, epfd.  The entry includes the file descriptor,
							  // fd, a reference to the  corresponding open file description (see epoll(7) and open(2)),
							  // and the settings specified in event.
			 fdServer,        // Target file descriptor
			 &ev              // Previously declared epoll_event
			) < 0
	   )
	{
		perror("Epoll_ctl fail");
		exit(errno);
	}
}

void Server::server_launch_start(int fdServer, int fdPoll, Server & server)
{
	int	ready;
	struct epoll_event	user[MAX_USERS];
	while (serverLife) {
		if ((ready = epoll_wait   // epoll_wait returns the numbers of FDs ready for IO; 0 if none; -1 if error
					(
					 fdPoll,      // == EPOLL fd
					 user,        // == EPOLL events TODO need explanations on events
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
			if (user[i].data.fd == fdServer) {
				server.newConnection();
			}
			else {
				server.requestClient(user[i]);
			}
		}
		pingTime();
		usleep(REFRESH_DELAY);
	}
	__debug_unknown(server);
}

