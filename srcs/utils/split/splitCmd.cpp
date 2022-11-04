/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:48:40 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/04 15:12:37 by adlancel         ###   ########.fr       */
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