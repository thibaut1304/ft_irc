/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:48:40 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 14:48:53 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	splitCmd(std::vector<std::string> & sCmd, std::string cmd) {

	size_t					pos = 0;
	std::string				delimiter = " \n\r";
	std::string::iterator	it;

	while ((pos = cmd.find_first_of(delimiter)) != std::string::npos)
	{
		sCmd.push_back(cmd.substr(0, pos));
		for (it = cmd.begin() + pos; it != cmd.end() && delimiter.find(*it) != std::string::npos; it++)
			pos++;
		cmd.erase(0, pos);
	}
<<<<<<< HEAD:srcs/utils/basic_utils.cpp
}
void split(std::vector<std::string> & sCmd, std::string cmd, std::string delimiter)
{

	size_t					pos = 0;
	std::string::iterator	it;
	
	while ((pos = cmd.find_first_of(delimiter)) != std::string::npos)
	{
		sCmd.push_back(cmd.substr(0, pos));
		for (it = cmd.begin() + pos; it != cmd.end() && delimiter.find(*it) != std::string::npos; it++)
			pos++;
		cmd.erase(0, pos);
	}
}

void	print_buff(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	for (;it != buff.end();it++) {
		std::cout << _RED << *it << _NC << std::endl;
	}
}

void		myToupper(std::string & emma) {
	std::string::iterator	it = emma.begin();

	for (; it != emma.end();it++)
		*it = std::toupper(*it);
=======
	int i = 0;
	while (std::isspace(cmd.c_str()[i])) i++;
	cmd.erase(0, i);
	if (!cmd.empty())
		sCmd.push_back(cmd.substr(0, pos));
>>>>>>> master:srcs/utils/split/splitCmd.cpp
}
