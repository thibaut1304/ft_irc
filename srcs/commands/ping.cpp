/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:13:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 15:51:35 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	ping(Server *serv, User user) {
	std::string msg = PING(std::string("TEST PING"));
	std::cout << msg << std::endl;
	send(user.getFd(), msg.c_str(), msg.length(), 0);
	std::cout << "CMD PING " << user.getFd() << " port number " << serv->getPort() << std::endl;
}

void	kill(Server *serv, User user) {
	std::cout << "CMD KILL " << user.getFd() << " port number " << serv->getPort() << std::endl;
		send(user.getFd(), "Le client doit etre kill\n", strlen("Le client doit etre kill\n"), 0);
	serv->killUserClient(user);
}