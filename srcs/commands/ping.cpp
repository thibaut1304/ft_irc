/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:13:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 14:55:19 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	ping(Server *serv, User user) {
	std::string msg = PING(std::string("TEST PING"));
	send(user.getFd(), msg.c_str(), msg.length(), 0);
	std::cout << "CMD PING " << user.getFd() << " port number " << serv->getPort() << std::endl;
}