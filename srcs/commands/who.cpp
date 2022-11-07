/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:39:21 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/06 14:47:09 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	who(Server *serv, User user) {
	if (serv->_allBuff.size() == 1) {
		std::string nick = "*";
		if (user.getValidUser() == true)
			nick =	user.getNickname();
		std::string msg = NAME + ERR_NEEDMOREPARAMS(print_cmd(serv->_allBuff), nick);
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->_allBuff));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else {

	}
}

// :irc.local 352 qq * 1 172.17.0.1 irc.local qq H :0 4
// :irc.local 315 qq qq :End of /WHO list.
