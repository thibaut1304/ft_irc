/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOTONCHANNEL.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:53:11 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/05 17:53:40 by wszurkow         ###   ########.fr       */
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
	Channel channel = server->getChannel(ch_name);
	return false;

}
