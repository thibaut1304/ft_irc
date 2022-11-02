/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:17 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 14:40:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	kill(Server *serv, User user) {
	std::cout << "CMD KILL " << user.getFd() << " port number " << serv->getPort() << std::endl;
		send(user.getFd(), "Le client doit etre kill\n", strlen("Le client doit etre kill\n"), 0);
	serv->killUserClient(user);
}