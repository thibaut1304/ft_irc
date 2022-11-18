/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:17 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/18 11:19:05 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	kill(Server *serv, User user) {
	if (Debug) {
		std::cout << "Reserved for admin! Check modes" << std::endl;
		std::cout << "CMD KILL " << user.getFd() << " port number " << serv->getPort() << std::endl;
		send(user.getFd(), "Le client doit etre kill\n", strlen("Le client doit etre kill\n"), 0);
	}
	serv->get_users()[user.getFd()].setIsKill(true);
	serv->killUserClient(user.getFd());

}
