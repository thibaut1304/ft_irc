/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:18:11 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 04:23:07 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


//    Command: INFO
//    Parameters: [<server>]

//    The INFO command is required to return information which describes
//    the server: its version, when it was compiled, the patchlevel, when
//    it was started, and any other miscellaneous information which may be
//    considered to be relevant.

//    Examples:

//    INFO csd.bu.edu                 ; request an INFO reply from
//    csd.bu.edu

//    :Avalon INFO *.fi               ; INFO request from Avalon for first
//    server found to match *.fi.

//    Numeric Replies:
//    [402]     ERR_NOSUCHSERVER "<server name> :No such server"
//    [371]     RPL_INFO         ":<string>"
//    [374]     RPL_ENDOFINFO    ":End of /INFO list"
//                    - A server responding to an INFO message is required to
//                      send all its 'info' in a series of RPL_INFO messages
//                      with a RPL_ENDOFINFO reply to indicate the end of the
//                      replies.

void info (Server * server, User user)
{
	(void)server;
	(void)user;
}
