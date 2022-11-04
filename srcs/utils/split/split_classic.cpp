/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_classic.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:49:57 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/04 15:51:19 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>

void	split(std::vector<std::string> & sCmd, std::string cmd, std::string delimiter) 
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
	int i = 0;
	while (std::isspace(cmd.c_str()[i])) i++;
	cmd.erase(0, i);
	if (!cmd.empty())
		sCmd.push_back(cmd.substr(0, pos));
}
