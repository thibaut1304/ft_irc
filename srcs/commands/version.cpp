/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:40:55 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/02 19:46:55 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


//    Command: VERSION
//    Parameters: [<server>]
//
//    The VERSION message is used  to  query  the  version  of  the  server
//    program.  An optional parameter <server> is used to query the version
//    of the server program which a client is not directly connected to.

//    Examples:
//    :Wiz VERSION *.se               ; message from Wiz to check the version
//                                    of a server matching "*.se"
//    VERSION tolsun.oulu.fi          ; check the version of server
//                                    "tolsun.oulu.fi".

//    Numeric Replies:
//
//    [351]     RPL_VERSION "<version>.<debuglevel> <server> :<comments>"
//    Reply by the server showing its version details.
//    The <version> is the version of the software being
//    used (including any patchlevel revisions) and the
//    <debuglevel> is used to indicate if the server is
//    running in "debug mode".
//    The "comments" field may contain any comments about
//    the version or further version details.

//    [402]     ERR_NOSUCHSERVER "<server name> :No such server"
//    Used to indicate the server name given currently
//    doesn't exist.


void version(Server * server, User user)
{
	(void)server;
	int destination = user.getFd();
	std::string msg;

	if (0) // TODO makes no sense - how do we check server name
	{
		msg =  ERR_NOSUCHSERVER("test");
		send_to_client(destination, msg);
		return ;
	}

	std::string debuglevel = Debug ? "1" : "0";

	msg += VERSION;
	msg += ".debuglevel0" + debuglevel + " ";
	msg += ":This is a comment describing our irc server\n";
	send_to_client(destination, msg, "351");
}
