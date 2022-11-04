/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOTREGISTERED.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:44:55 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/04 15:45:12 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NOTREGISTERED(User user, std::string command)
{
	int  destination = user.getFd();
	STR_ msg;

	if (user.getValidUser() == false)
	{
		msg = ERR_NOTREGISTERED_(command);
		send_to_client(destination, msg);
		return NOT_OK_;
	}
	return OK_;
}
