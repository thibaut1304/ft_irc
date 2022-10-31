/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:35:20 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 17:35:31 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

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

void	kill(Server *serv, User user) {
	std::cout << "CMD KILL " << user.getFd() << " port number " << serv->getPort() << std::endl;
		send(user.getFd(), "Le client doit etre kill\n", strlen("Le client doit etre kill\n"), 0);
	serv->killUserClient(user);
}