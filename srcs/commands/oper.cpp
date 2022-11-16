/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:36:12 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/16 16:46:49 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void oper(Server *server, User user)
{
	if (check_ERR_NEEDMOREPARAMS (server, user)         == NOT_OK_) return ;


	Server::map_users::iterator it = server->_users.begin();
	Server::map_users::iterator ite = server->_users.end();
	while (it != ite)
		if (it->second.getNickname() == user.getNickname())
			break;

	// Invalid pass
	//        464     ERR_PASSWDMISMATCH
	//                        ":Password incorrect"

	server->add_server_operator("TEST");

	std::string msg;
	msg = ":" + NAME_V + " 381 " + user.getNickname() +  " :You are now an IRC operator\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);
}

//4.1.5 Oper
//
//Command: OPER
//Parameters: <user> <password>
//
//OPER message is used by a normal user to obtain operator privileges.
//The combination of <user> and <password> are required to gain
//Operator privileges.
//
//If the client sending the OPER command supplies the correct password
//for the given user, the server then informs the rest of the network
//of the new operator by issuing a "MODE +o" for the clients nickname.
//
//The OPER message is client-server only.
//
//Numeric Replies:
//
//ERR_NEEDMOREPARAMS              RPL_YOUREOPER
//ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
//
//Example:
//
//OPER foo bar                    ; Attempt to register as an operator
//using a username of "foo" and "bar" as
//the password.


