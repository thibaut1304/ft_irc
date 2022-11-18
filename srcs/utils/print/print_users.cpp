/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_users.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:06:59 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/18 11:21:48 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Channel::printUsers(void)
{
	map_users map = getUsers();
	map_users::iterator it = map.begin();
	map_users::iterator ite = map.end();

	while (it != ite)
	{
		if (Debug) {
			std::cout << "Username : " << (*it).first << std::endl;
			std::cout << "FD : " << (*it).second->getFd() << std::endl;
		}
		it++;
	}
}
