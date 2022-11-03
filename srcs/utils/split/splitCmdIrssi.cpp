/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitCmdIrssi.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:47:34 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 14:48:02 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	splitCmdIrssi(std::vector<std::string> & sCmd, std::string cmd) {

	size_t					pos = 0;
	std::string				delimiter = "\r\n";
	std::string::iterator	it;

	while ((pos = cmd.find_first_of(delimiter)) != std::string::npos)
	{
		sCmd.push_back(cmd.substr(0, pos));
		for (it = cmd.begin() + pos; it != cmd.end() && delimiter.find(*it) != std::string::npos; it++)
			pos++;
		cmd.erase(0, pos);
	}
}
