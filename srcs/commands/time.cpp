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

	int                  destination = user.getFd();
	std::string          msg;
	std::stringstream    server_time;

	if (check_ERR_NOTREGISTERED(server, user) == NOT_OK_) return ;
	if (check_ERR_NOSUCHSERVER (server, user) == NOT_OK_) return ;

	server_time        \
		<< get_charday() \
		<< " " \
		<< ((get_day() < 10) ? "0" : "") \
		<< get_day()   \
		<< "/"         \
		<< ((get_month() < 10) ? "0" : "") \
		<< get_month() \
		<< "/"         \
		<< get_year()  \
		<< " "         \
		<< get_hour()  \
		<< ":"         \
		<< ((get_minute() < 10) ? "0" : "") \
		<< get_minute() \
		<< ":"         \
		<< ((get_seconds() < 10) ? "0" : "") \
		<< get_seconds() \
		<< " CET"
		<< std::endl;

	msg =  NAME_V;
	msg += " ";
	msg += ":";
	msg += server_time.str();
	send_to_client(destination, msg, "391");
}
