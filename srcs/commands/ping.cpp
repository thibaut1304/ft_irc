/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:13:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 18:36:30 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	ping(Server *serv, User user) {
	std::string msg = PING(std::string("TEST PING"));
	std::cout << msg << std::endl;
	send(user.getFd(), msg.c_str(), msg.length(), 0);
	std::cout << "CMD PING " << user.getFd() << " port number " << serv->getPort() << std::endl;
}
