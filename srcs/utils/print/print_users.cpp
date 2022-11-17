/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_users.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:06:59 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/17 17:25:11 by wszurkow         ###   ########.fr       */
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
		std::cout << "Username : " << (*it).first << std::endl;
		std::cout << "FD : " << (*it).second->getFd() << std::endl;
		it++;
	}
}
