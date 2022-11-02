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


void time(Server * server, User user)
{
(void)server;
	std::stringstream ss;
	std::string msg;

	ss << get_hour() << ":" << get_minute();

	msg = ss.str();

	send_to_client(user, msg );

}
