/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:24:21 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 17:26:47 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header_wsz.hpp"
#include "Server.hpp"


//   Command: ADMIN
//   Parameters: [<server>]
//
//   The admin message is used to find the name of the administrator of
//   the given server, or current server if <server> parameter is omitted.
//   Each server must have the ability to forward ADMIN messages to other
//   servers.
//
//   Numeric Replies:
//           ERR_NOSUCHSERVER
//           RPL_ADMINME                     RPL_ADMINLOC1
//           RPL_ADMINLOC2                   RPL_ADMINEMAIL
//
//   Examples:
//   ADMIN tolsun.oulu.fi            ; request an ADMIN reply from
//                                   tolsun.oulu.fi
//
//   :WiZ ADMIN *.edu                ; ADMIN request from WiZ for first
//                                   server found to match *.edu.

//   Numeric Error Replies:
//        256     RPL_ADMINME
//                        "<server> :Administrative info"
//        257     RPL_ADMINLOC1
//                        ":<admin info>"
//        258     RPL_ADMINLOC2
//                        ":<admin info>"
//        259     RPL_ADMINEMAIL
//                        ":<admin info>"
//
//                        - When replying to an ADMIN message, a server
//                          is expected to use replies RLP_ADMINME
//                          through to RPL_ADMINEMAIL and provide a text
//                          message with each.  For RPL_ADMINLOC1 a
//                          description of what city, state and country
//                          the server is in is expected, followed by
//                          details of the university and department
//                          (RPL_ADMINLOC2) and finally the administrative
//                          contact for the server (an email address here
//                          is required) in RPL_ADMINEMAIL.

void admin(Server * server, User user)
{
	if (check_ERR_NOSUCHSERVER(server, user))
		return ;

}
