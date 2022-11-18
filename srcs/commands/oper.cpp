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

/* ========================================================================== */
/* --------------------------------- UTILS ---------------------------------- */
/* ========================================================================== */
static User * oper_get_user_ptr(Server *server, User user)
{
	(void)user;
	Server::map_users::iterator  users_it  = server->_users.begin();
	Server::map_users::iterator  users_ite = server->_users.end();

	while (users_it != users_ite)
	{
		if (user.getNickname() == users_it->second.getNickname())
			return &(users_it->second);
		users_it++;
	}
	return NULL;
}

/* ========================================================================== */
/* --------------------------------- CHECKS --------------------------------- */
/* ========================================================================== */
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
	std::string server_login = bit[1];
	std::string server_key   = bit[2];
	if (server_login != SERVER_LOGIN || server_key != SERVER_PASSWORD)
	{
		msg = ":" + NAME_V + " 491 " + __USER__ + " :Invalid oper credentials.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_ ;
	}
	return OK_ ;
}

static bool oper_check_ERR_ALREADYOPERATOR(Server * server, User user)
{
	(void)server;
	std::string msg;
	if (user.get_is_operator() == true)
	{
		// NOTE 493 does not exist in rfc
		msg = ":" + NAME_V + " 493 " + __USER__ + " :User is already an operator.\r\n";
		send(user.getFd(), msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}

/* ========================================================================== */
/* ---------------------------------- SEND ---------------------------------- */
/* ========================================================================== */

static void notify_everyone_new_operator_created(Server *server, User user)
{
	std::string msg;
	Server::map_users           users = server->get_users();
	Server::map_users::iterator it    = users.begin();
	Server::map_users::iterator ite   = users.end();

	while (it != ite)
	{
		msg = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getIp() + " :";
		msg += user.getNickname() + " ";
		msg += "has been promoted to server operator\r\n";
		if (it->second.getNickname() != user.getNickname())
			send(it->second.getFd(), msg.c_str(), msg.length(), 0);
		it++;
	}
}

static void send_RPL_YOUREOPER(User user)
{
	std::string msg;
	msg =  ":" + NAME_V;
	msg += " 381 " ;
	msg += user.getNickname();
	msg += " :You are now an IRC operator\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);
}

/* ========================================================================== */
/* ---------------------------------- MAIN ---------------------------------- */
/* ========================================================================== */
void oper(Server *server, User user)
{
	if (oper_check_ERR_NEEDMOREPARAMS (server, user) == NOT_OK_) { return ; }
	if (check_ERR_NOTREGISTERED       (server, user) == NOT_OK_) { return ; }
	if (oper_check_ERR_PASSWDMISMATCH (server, user) == NOT_OK_) { return ; }
	if (oper_check_ERR_ALREADYOPERATOR(server, user) == NOT_OK_) { return ; }

	User * userptr = oper_get_user_ptr(server, user);
	userptr->set_is_operator(true);

	send_RPL_YOUREOPER(user);
	notify_everyone_new_operator_created(server, user);
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


