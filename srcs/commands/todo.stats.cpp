/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:29:19 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 17:39:12 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void stats(Server *server, User user)
{
	if (check_ERR_NOSUCHSERVER(server, user))
		return ;
}

// 4.3.2 Stats message

// Command: STATS
// Parameters: [<query> [<server>]]

// The stats message is used to query statistics of certain server.  If
// <server> parameter is omitted, only the end of stats reply is sent
// back.  The implementation of this command is highly dependent on the
// server which replies, although the server must be able to supply
// information as described by the queries below (or similar).

// A query may be given by any single letter which is only checked by
// the destination server (if given as the <server> parameter) and is
// otherwise passed on by intermediate servers, ignored and unaltered.
// The following queries are those found in the current IRC
// implementation and provide a large portion of the setup information
// for that server.  Although these may not be supported in the same way
// by other versions, all servers should be able to supply a valid reply
// to a STATS query which is consistent with the reply formats currently
// used and the purpose of the query.

// The currently supported queries are:

// c - returns a list of servers which the server may connect
// to or allow connections from;
// h - returns a list of servers which are either forced to be
// treated as leaves or allowed to act as hubs;
// i - returns a list of hosts which the server allows a client
// to connect from;
// k - returns a list of banned username/hostname combinations
// for that server;
// l - returns a list of the server's connections, showing how
// long each connection has been established and the traffic
// over that connection in bytes and messages for each
// direction;
// m - returns a list of commands supported by the server and
// the usage count for each if the usage count is non zero;
// o - returns a list of hosts from which normal clients may
// become operators;
// y - show Y (Class) lines from server's configuration file;
// u - returns a string showing how long the server has been up.


// Examples:

// STATS m                         ; check the command usage for the server
// you are connected to

// :Wiz STATS c eff.org            ; request by WiZ for C/N line
// information from server eff.org



// Numeric Replies:

// ERR_NOSUCHSERVER
// RPL_STATSCLINE                  RPL_STATSNLINE
// RPL_STATSILINE                  RPL_STATSKLINE
// RPL_STATSQLINE                  RPL_STATSLLINE
// RPL_STATSLINKINFO               RPL_STATSUPTIME
// RPL_STATSCOMMANDS               RPL_STATSOLINE
// RPL_STATSHLINE                  RPL_ENDOFSTATS


//211     RPL_STATSLINKINFO
//"<linkname> <sendq> <sent messages>
//<sent bytes> <received messages>
//<received bytes> <time open>"
//
//212     RPL_STATSCOMMANDS
//"<command> <count>"

//213     RPL_STATSCLINE
//"C <host> * <name> <port> <class>"

//214     RPL_STATSNLINE
//"N <host> * <name> <port> <class>"

//215     RPL_STATSILINE
//"I <host> * <host> <port> <class>"

//216     RPL_STATSKLINE
//"K <host> * <username> <port> <class>"

//218     RPL_STATSYLINE
//"Y <class> <ping frequency> <connect
//frequency> <max sendq>"

//219     RPL_ENDOFSTATS
//"<stats letter> :End of /STATS report"

//241     RPL_STATSLLINE
//"L <hostmask> * <servername> <maxdepth>"

//242     RPL_STATSUPTIME
//":Server Up %d days %d:%02d:%02d"

//243     RPL_STATSOLINE
//"O <hostmask> * <name>"

//244     RPL_STATSHLINE
//"H <hostmask> * <servername>"


