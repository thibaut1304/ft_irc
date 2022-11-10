/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.check_ERR_NOSUCHNICK.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 01:02:41 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/08 01:04:57 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NOSUCHNICK(Server * server, User user)
{
	int                  destination = user.getFd();
	VEC_<STR_>           buffer      = server->_allBuff;
	VEC_<STR_>::iterator it          = buffer.begin();
	std::string msg;

}
