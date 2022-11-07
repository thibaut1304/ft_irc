/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:27:15 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/06 14:37:43 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::initCmd() {

	/* ====================================================================== */
	/* ----------------------------- MANDATORY ------------------------------ */
	/* ====================================================================== */

	_listCmd["CAP"]          = &cap;

	// # REGISTRATION
	_listCmd["PASS"]          = &pass;
	_listCmd["NICK"]          = &nick;
	_listCmd["USER"]          = &user;
	_listCmd["QUIT"]          = &quit;

	// # CHANNEL OPERATIONS
	_listCmd["JOIN"]          = &join;
	//_listCmd["PART"]          = &part;    // TODO
	//_listCmd["MODE"]          = &mode;    // TODO
	//_listCmd["CHANNEL MODES"] = &;        // TODO
	//_listCmd["USER MODES"]    = &;        // TODO
	_listCmd["TOPIC"]         = &topic;   // TODO
	//_listCmd["INVITES"]       = &invites; // TODO
	//_listCmd["KICK"]          = &kick;    // TODO

	// # SENDING MESSAGES
	_listCmd["PRIVMSG"]       = &privmsg;
	_listCmd["NOTICE"]        = &notice;

	// # USER BASED QUERIES
	_listCmd["WHO"]           = &who;      // TODO

	// # MISC MESSAGES
	_listCmd["KILL"]          = &kill;
	_listCmd["PING"]          = &ping;
	//_listCmd["PONG"]          = &pong;
	//_listCmd["ERROR"]         = &error;

	/* ====================================================================== */
	/* ------------------------------ OPTIONAL ------------------------------ */
	/* ====================================================================== */
	// # REGISTRATION
	//_listCmd["SERVER"]        = &server; // TODO ?  The server message is used to tell a server that the other end of a new connection is a server.
	//_listCmd["OPER"]          = &oper;
	//_listCmd["SQUIT"]         = &squit;

	// # CHANNEL OPERATIONS
	//_listCmd["NAMES"]         = &names;
	//_listCmd["LIST"]          = &list;

	// # SERVER QUERIES AND COMMANDS
	_listCmd["VERSION"]       = &version;
	_listCmd["TIME"]          = &time;
	_listCmd["INFO"]          = &info;
	//_listCmd["STATS"]       = &stats;
	//_listCmd["LINKS"]       = &links;
	//_listCmd["CONNECT"]     = &connect; // NOTE IRSSI command not to do
	//_listCmd["TRACE"]       = &trace;
	//_listCmd["ADMIN"]       = &admin;

	// # USER BASED QUERIES
	//_listCmd["WHOIS"]         = &whois;
	//_listCmd["WHOWAS"]        = &whowas;


	// # OPTIONAL MESSAGES
	_listCmd["MOTD"]          = &motd;
	//_listCmd["AWAY"]          = &away;
	//_listCmd["REHASH"]        = &rehash;
	//_listCmd["RESTART"]       = &restart;
	//_listCmd["SUMMON"]        = &summon;
	//_listCmd["USERS"]         = &users;
	//_listCmd["WALLOPS"]       = &wallops;
	//_listCmd["USERHOST"]      = &userhost;
	//_listCmd["ISON"]          = &ison;

}

