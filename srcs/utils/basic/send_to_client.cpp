/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_client.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:52:31 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 14:52:37 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void send_to_client(int fd, std::string code, std::string msg)
{
	int delay = 0;
	std::string buffer;

	if (Debug)
		buffer += code + " ";
	buffer += msg;

	send(fd, buffer.c_str(), buffer.length(), delay);
}
