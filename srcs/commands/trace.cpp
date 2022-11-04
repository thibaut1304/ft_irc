/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:27:36 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 17:38:34 by wsz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void trace(Server *server, User user)
{
	if (check_ERR_NOSUCHSERVER(server, user))
		return ;
}

//Command: TRACE
//Parameters: [<server>]

//TRACE command is used to find the route to specific server.  Each
//server that processes this message must tell the sender about it by
//sending a reply indicating it is a pass-through link, forming a chain
//of replies similar to that gained from using "traceroute".  After
//sending this reply back, it must then send the TRACE message to the
//next server until given server is reached.  If the <server> parameter
//is omitted, it is recommended that TRACE command send a message to
//the sender telling which servers the current server has direct
//connection to.

//If the destination given by "<server>" is an actual server, then the
//destination server is required to report all servers and users which
//are connected to it, although only operators are permitted to see
//users present.  If the destination given by <server> is a nickname,
//they only a reply for that nickname is given.


//Examples:

//TRACE *.oulu.fi                 ; TRACE to a server matching *.oulu.fi
//:WiZ TRACE AngelDust            ; TRACE issued by WiZ to nick AngelDust


//Numeric Replies:

//ERR_NOSUCHSERVER

//If the TRACE message is destined for another server, all intermediate
//servers must return a RPL_TRACELINK reply to indicate that the TRACE
//passed through it and where its going next.

//RPL_TRACELINK
//A TRACE reply may be composed of any number of the following numeric
//replies.

//RPL_TRACECONNECTING             RPL_TRACEHANDSHAKE
//RPL_TRACEUNKNOWN                RPL_TRACEOPERATOR
//RPL_TRACEUSER                   RPL_TRACESERVER
//RPL_TRACESERVICE                RPL_TRACENEWTYPE
//RPL_TRACECLASS

//200     RPL_TRACELINK
//"Link <version & debug level> <destination>
//<next server>"

//201     RPL_TRACECONNECTING
//"Try. <class> <server>"

//202     RPL_TRACEHANDSHAKE
//"H.S. <class> <server>"

//203     RPL_TRACEUNKNOWN
//"???? <class> [<client IP address in dot form>]"

//204     RPL_TRACEOPERATOR
//"Oper <class> <nick>"

//205     RPL_TRACEUSER
//"User <class> <nick>"

//206     RPL_TRACESERVER
//"Serv <class> <int>S <int>C <server>
//<nick!user|*!*>@<host|server>"

//208     RPL_TRACENEWTYPE
//"<newtype> 0 <client name>"

//261     RPL_TRACELOG
//"File <logfile> <debug level>"

//- The RPL_TRACE* are all returned by the server in
//response to the TRACE message.  How many are
//returned is dependent on the the TRACE message and


//whether it was sent by an operator or not.  There
//is no predefined order for which occurs first.
//Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
//RPL_TRACEHANDSHAKE are all used for connections
//which have not been fully established and are either
//unknown, still attempting to connect or in the
//process of completing the 'server handshake'.
//RPL_TRACELINK is sent by any server which handles
//a TRACE message and has to pass it on to another
//server.  The list of RPL_TRACELINKs sent in
//response to a TRACE command traversing the IRC
//network should reflect the actual connectivity of
//the servers themselves along that path.
//RPL_TRACENEWTYPE is to be used for any connection
//which does not fit in the other categories but is
//being displayed anyway.

