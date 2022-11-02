/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:40:55 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/02 18:56:17 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void send_to_client(User u, std::string msg, size_t delay = 0)
{
	send(u.getFd(), msg.c_str(), msg.length(), delay);
}

void version(Server * server, User user)
{
	(void)server;
	send_to_client(user, VERSION);
}
