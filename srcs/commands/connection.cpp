/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:56:39 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 15:10:44 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void 	Server::acceptUser(User user) {
	std::string msg_01 = NAME;
	msg_01.append(" 001 ");
	msg_01.append(user.getNickname());
	msg_01.append(" ");
	msg_01 += RPL_WELCOME(user.getNickname(), user.getUsername(), user.getHostname());
	if (send(user.getFd(), msg_01.c_str(), msg_01.length(), 0) < 0) {
		perror("Error send msg 001");
		exit(errno);
	}
	std::string msg_02 = NAME + " 002 " + user.getNickname() + " " + RPL_YOURHOST(NAME, VERSION);
	if (send(user.getFd(), msg_02.c_str(), msg_02.length(), 0) < 0) {
		perror("Error send msg 001");
		exit(errno);
	}
	std::string msg_03 = NAME;
	msg_03 += " 003 " + user.getNickname() + " ";
	msg_03 += RPL_CREATED(DATE);
	if (send(user.getFd(), msg_03.c_str(), msg_03.length(), 0) < 0) {
		perror("Error send msg 001");
		exit(errno);
	}
	std::string msg_04 = NAME;
	msg_04 += " 004 " + user.getNickname() + " ";
	msg_04 += RPL_MYINFO(NAME, VERSION, "user mode", "channel mode");
	if (send(user.getFd(), msg_04.c_str(), msg_04.length(), 0) < 0) {
		perror("Error send msg 001");
		exit(errno);
	}
}