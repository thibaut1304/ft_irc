/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:27:15 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/02 17:57:19 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::initCmd() {
	_listCmd["CAP"]          = &cap;


	// # REGISTRATION
	_listCmd["PASS"]          = &pass;
	_listCmd["NICK"]          = &nick;
	_listCmd["USER"]          = &user;
	//_listCmd["SERVER"]        = &server;
	//_listCmd["OPER"]          = &oper;
	//_listCmd["QUIT"]          = &quit;
	//_listCmd["SQUIT"]         = &squit;

	// # CHANNEL OPERATIONS
	//_listCmd["JOIN"]          = &join;
	//_listCmd["PART"]          = &part;
	//_listCmd["MODE"]          = &mode;
	//_listCmd["CHANNEL MODES"] = &; // TODO ?
	//_listCmd["USER MODES"]    = &; // TODO ?
	//_listCmd["TOPIC"]         = &topic;
	//_listCmd["NAMES"]         = &names;
	//_listCmd["LIST"]          = &list;
	//_listCmd["INVITES"]       = &invites;
	//_listCmd["KICK"]          = &kick;

	// # SERVER QUERIES AND COMMANDS
	_listCmd["VERSION"]       = &version;
	//_listCmd["STATS"]         = &stats;
	//_listCmd["LINKS"]         = &links;
	//_listCmd["TIME"]          = &time;
	//_listCmd["CONNECT"]       = &connect;
	//_listCmd["TRACE"]         = &trace;
	//_listCmd["ADMIN"]         = &admin;
	//_listCmd["INFO"]          = &info;

	// # SENDING MESSAGES
	//_listCmd["PRIVMSG"]       = &privmsg;
	//_listCmd["NOTICE"]        = &notice;

	// # USER BASED QUERIES
	//_listCmd["WHO"]           = &who;
	//_listCmd["WHOIS"]         = &whois;
	//_listCmd["WHOWAS"]        = &whowas;

	// # MISC MESSAGES
	_listCmd["KILL"]          = &kill;
	_listCmd["PING"]          = &ping;
	//_listCmd["PONG"]          = &pong;
	//_listCmd["ERROR"]         = &error;

	// # OPTIONAL MESSAGES
	//_listCmd["AWAY"]          = &away;
	//_listCmd["REHASH"]        = &rehash;
	//_listCmd["RESTART"]       = &restart;
	//_listCmd["SUMMON"]        = &summon;
	//_listCmd["USERS"]         = &users;
	//_listCmd["WALLOPS"]       = &wallops;
	//_listCmd["USERHOST"]      = &userhost;
	//_listCmd["ISON"]          = &ison;
}

