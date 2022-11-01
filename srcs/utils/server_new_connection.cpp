/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_new_connection.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 05:40:21 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/01 05:40:40 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int server_new_connection_accept(int fdServer, sockaddr_in & clientAddress, int size)
{
	int new_conn_fd;
	std::string msg = "ERROR : Server is full !\n";
	socklen_t	addrlen = sizeof(clientAddress);

	memset(&clientAddress, 0, addrlen);
	new_conn_fd = accept(fdServer, (struct sockaddr*)&clientAddress, &addrlen);
	if (size >= MAX_USERS) {
		send(new_conn_fd, msg.c_str(), msg.length(), 0);
		close(new_conn_fd);
		exit (1); // TODO Correct return value
	}
	return new_conn_fd;
}

void server_new_connection_epoll_ctl(int fdNew, int fdPoll)
{
	struct epoll_event  ev;
	memset(&ev, 0, sizeof(struct epoll_event));
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fdNew;
	if (epoll_ctl(fdPoll, EPOLL_CTL_ADD, fdNew, &ev) < 0) {
		perror("Epoll ctl User fail");
		exit(errno);
	}
}
