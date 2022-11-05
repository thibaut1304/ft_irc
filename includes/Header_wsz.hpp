/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header_wsz.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:12:09 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 16:21:54 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Server.hpp"

#define PNL_(str) std::cout << str << std::endl;
#define P_(str)   std::cout << str;
#define STR_      std::string
#define VEC_      std::vector
#define OK_       1
#define NOT_OK_   0

bool check_ERR_NOSUCHSERVER(Server *server, User user);
bool check_ERR_NOTREGISTERED(User user, std::string cmd);
bool check_ERR_NEEDMOREPARAMS(Server *server, User user);
bool check_ERR_NOTONCHANNEL(Server *server, User user);

//struct CmdStruct_ {
	//int                  _destination;
	//VEC_<STR_>           _buffer     ;
	//VEC_<STR_>::iterator _begin      ;
	//size_t               _size;
	//std::string          _msg;

	//CmdStruct_ (Server *server, User user)
	//{
		//_destination = user.getFd();
		//_buffer      = server->_allBuff;
		//_size        = _buffer.size();
		//_begin       = _buffer.begin();
	//}
//} ;
