/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOTONCHANNEL.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:53:11 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/07 21:50:18 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

bool check_ERR_NOTONCHANNEL(Server *server, User user)
{
	(void)user;
	BUFFER_           buffer  = server->_allBuff;
	BUFFER_::iterator it      = buffer.begin();
	std::string       ch_name = *it;
	Channel *channel = server->getChannel(ch_name);
	(void)channel;
	return false;
}
