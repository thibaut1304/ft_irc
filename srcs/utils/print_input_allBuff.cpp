/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input_allBuff.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:58:01 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 15:59:30 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

std::string print_cmd(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	return (*it);
}

std::string	print_allBuff(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = ++buff.begin();
	std::string msg;
	
	for (;it != buff.end(); it++) {
		msg+= *it;
		if (it != --buff.end())
			msg += " ";
	}
	return (msg);
}