/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:44:25 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/02 19:55:52 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#define STR std::string

// 391     RPL_TIME "<server> :<string showing server's local time>"
//
// When replying to the TIME message, a server must send
// the reply using the RPL_TIME format above.  The string
// showing the time need only contain the correct day and
// time there.  There is no further requirement for the
// time string.

// 402     ERR_NOSUCHSERVER "<server name> :No such server"
//
// Used to indicate the server name given currently
// doesn't exist.

void time(Server * server, User user)
{
	(void)server;

	int destination = user.getFd();
	std::stringstream server_time;
	std::string msg;

	server_time         \
		<< " "          \
		<< get_hour()   \
		<< ":"          \
		<< get_minute() \
		<< std::endl;


	if (NAME != NAME) // TODO makes no sense - how do we check server name
	{
		msg =  NAME;
		msg += " :No such server";
		send_to_client(destination, "402",  msg);
		return ;
	}

	msg =  NAME;
	msg += server_time.str();
	send_to_client(destination, "391",  msg);
}
