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

#define __USER__ (user.getNickname().size() > 0 ? user.getNickname() : "*")

static bool oper_check_ERR_NEEDMOREPARAMS(Server *server, User user)
{
	std::string msg;
	BUFFER_ buffer = server->_allBuff;
	if (buffer.size() < 3)
	{
		msg = ":" + NAME_V + " 461 " + __USER__ + " OPER " + ":Not enough parameters.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_ ;
	}
	return OK_;
}

static bool oper_check_ERR_PASSWDMISMATCH(Server *server, User user)
{
	BUFFER_ buffer = server->_allBuff;
	BUFFER_::iterator bit = buffer.begin();
	std::string msg;
	std::string server_key = bit[2];
	if (server_key != SERVER_PASSWORD)
	{
		msg = ":" + NAME_V + " 491 " + __USER__ + " :Invalid oper credentials.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_ ;
	}
	return OK_ ;
}

static bool oper_check_ERR_OPERNICKTAKEN(Server *server, User user)
{
	BUFFER_ buffer = server->_allBuff;
	BUFFER_::iterator bit = buffer.begin();
	std::string msg;
	std::string operator_name = bit[1];
	if (server->does_operator_name_exist(operator_name) == true)
	{
		// NOTE 492 does not exist in rfc
		msg = ":" + NAME_V + " 492 " + __USER__ + " :Operator username already in use.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}

static bool oper_check_ERR_ALREADYOPERATOR(Server * server, User user)
{
	std::string op_name = server->is_this_user_an_operator(user.getNickname());
	std::string msg;
	if (op_name.size() > 0)
	{
		// NOTE 493 does not exist in rfc
		msg = ":" + NAME_V + " 493 " + __USER__ + " :User is already an operator.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}


void oper(Server *server, User user)
{
	std::string msg;
	BUFFER_ buffer = server->_allBuff;
	BUFFER_::iterator bit = buffer.begin();

	if (oper_check_ERR_NEEDMOREPARAMS (server, user) == NOT_OK_) { return ; }
	if (oper_check_ERR_PASSWDMISMATCH (server, user) == NOT_OK_) { return ; }
	if (oper_check_ERR_OPERNICKTAKEN  (server, user) == NOT_OK_) { return ; }
	if (oper_check_ERR_ALREADYOPERATOR(server, user) == NOT_OK_) { return ; }

	std::string operator_name = bit[1];
	server->add_server_operator(user.getNickname(), operator_name);
	msg = ":" + NAME_V + " 381 " + user.getNickname() +  " :You are now an IRC operator\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);

	Server::map_users users = server->get_users();
	Server::map_users::iterator it = users.begin();
	Server::map_users::iterator ite = users.end();

	while (it != ite)
	{
		msg = ":" + user.getNickname() + "!" + user.getHostname() + "@" + user.getIp() + " :";
		msg += user.getNickname() + " ";
		msg += "has been promoted to server operator\r\n";
		if (it->second.getNickname() != user.getNickname())
			send(it->second.getFd(), msg.c_str(), msg.length(), 0);
		it++;
	}
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


