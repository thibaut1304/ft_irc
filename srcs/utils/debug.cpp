/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 05:42:56 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/01 05:46:34 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void __debug_newConnection(std::string ip)
{
#if Debug
	std::cout << "Your IP is : " << _BLUE << ip << _NC << std::endl;
#endif
}

void	__debug_requestClient(char *buff)
{
#if Debug
	std::cout << _BLUE << buff << _NC;
#endif
}

void __debug_exploreCmd(void)
{
#if Debug
	std::cout << "CMD PING" << std::endl;
#endif
}



void   __debug_unknown(void) // TODO find corresponding method to debug
{
//#if Debug
	//std::cout << "Print number users : " << _GREEN << _users.size() << _NC << std::endl;
	//typedef std::map<const int, User>::iterator it;
	//for (it e = _users.begin() ; e != _users.end(); e++) {
		//std::cout << "FD : " << _YELLOW << e->first << _NC;
		//if (e != --_users.end())
			//std::cout << ", ";
		//else
			//std::cout << ".\n";
	//}
//#endif
}
