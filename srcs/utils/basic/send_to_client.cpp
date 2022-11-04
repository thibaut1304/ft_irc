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

void send_to_client(int fd, std::string msg, std::string err_code)
{
	int delay = 0;
	std::string buffer = NAME + " ";

	if (err_code != "" && Debug == 1)
		buffer += err_code + " ";
	buffer += msg;

	send(fd, buffer.c_str(), buffer.length(), delay);
}
