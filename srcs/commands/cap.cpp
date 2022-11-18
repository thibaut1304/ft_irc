/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:51:27 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/18 11:15:45 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	cap(Server *serv, User user) {
	if (Debug)
		std::cout << _CYAN << "CMD CAP" << _NC << std::endl;
	if (user.getValidUser()) {
		std::string msg = NAME + ERR_UNKNOWNCOMMAND(user.getNickname(), print_cmd(serv->get_allBuff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	return ;
}
