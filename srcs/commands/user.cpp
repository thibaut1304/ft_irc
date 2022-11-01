/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:11:56 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 20:56:00 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

static std::string	findPoint(std::vector<std::string> & all) {
	std::vector<std::string>::iterator it = all.begin();
	int i = 0;
	for (; it != all.end();it++, i++) {
		if (it->c_str()[0] == ':') {
			break;
		}
	}
	std::string bis;
	std::vector<std::string>::iterator copy = it;
	for(; it != all.end(); it++) {
		bis += *it;
		if (it != --all.end())
			bis += " ";
	}
	std::string::iterator it_str = bis.begin();
	for (; it_str != bis.end();it_str++) {
		if (*it_str != ' ' && *it_str != '\t' && *it_str != ':')
			break;
	}
	if (it_str != bis.begin())
		bis.erase(bis.begin(), it_str);
	all.erase(copy, all.end());
	return (bis);
}

void	user(Server *serv, User user) {
	std::vector<std::string> all;
	
	std::string bis = findPoint(serv->_allBuff);

	if (bis.empty() || serv->_allBuff.size != 4)
		std::cout << "Generer une erreur 461"<< std::endl;
	if (user.getValidUser() == false)
		std::cout << "Generer une erreur 462"<< std::endl;
	
	// splitCmdUser(all, serv->_buff);
	print_buff(serv->_allBuff);
	std::cout << _YELLOW << bis << _NC << std::endl;
	// print_buff(serv->_allBuff);
	// std::vector<std::string>::iterator it = --all.end();
	
	(void)user;
	// splitCmd(_allBuff, buff);
}