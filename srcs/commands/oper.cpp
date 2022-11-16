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
#include "connectionReplies.hpp"

void oper(Server *server, User user)
{
	std::string msg;
	BUFFER_ buffer = server->_allBuff;
	BUFFER_::iterator bit = buffer.begin();


	Server::map_users::iterator it = server->_users.begin();
	Server::map_users::iterator ite = server->_users.end();
	while (it != ite)
		if (it->second.getNickname() == user.getNickname())
			break;

	if (buffer.size() < 3)
	{
		msg = ":" + NAME_V + " 461 " + user.getNickname() + " OPER " + ":Not enough parameters.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return ;
	}

	std::string server_key = bit[2];
	if (server_key != SERVER_PASSWORD)
	{
		msg = ":" + NAME_V + " 491 " + user.getNickname() + " :Invalid oper credentials.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return ;
	}

	std::string operator_name = bit[1];
	if (server->does_operator_name_exist(operator_name) == true)
	{
		// NOTE 492 does not exist in rfc
		msg = ":" + NAME_V + " 492 " + user.getNickname() + " :Operator username already in use.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return ;
	}
	server->add_server_operator(operator_name);

	msg = ":" + NAME_V + " 381 " + user.getNickname() +  " :You are now an IRC operator\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);

	// TODO add notice
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
//ERR_NOOPERHOST // TODO? not in rfc                 ERR_PASSWDMISMATCH // TODO? not in rfc
//
//Example:
//
//OPER foo bar                    ; Attempt to register as an operator
//using a username of "foo" and "bar" as
//the password.


