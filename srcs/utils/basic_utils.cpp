/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:23:13 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/02 17:33:54 by thhusser         ###   ########.fr       */
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

void	splitCmdUser(std::vector<std::string> & sCmd, std::string cmd) {

	size_t					pos = 0;
	std::string				delimiter = ":\r\n";
	std::string::iterator	it;

	while ((pos = cmd.find_first_of(delimiter)) != std::string::npos)
	{
		sCmd.push_back(cmd.substr(0, pos));
		for (it = cmd.begin() + pos; it != cmd.end() && delimiter.find(*it) != std::string::npos; it++)
			pos++;
		cmd.erase(0, pos);
	}
}

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
	int i = 0;
	while (std::isspace(cmd.c_str()[i])) i++;
	cmd.erase(0, i);
	if (!cmd.empty())
		sCmd.push_back(cmd.substr(0, pos));
}

void	print_buff(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	for (int i = 1;it != buff.end();it++, i++) {
		std::cout << "LIGNE : " << i << " " <<_RED << *it << _NC << std::endl;
	}
}

void		myToupper(std::string & emma) {
	std::string::iterator	it = emma.begin();

	for (; it != emma.end();it++)
		*it = std::toupper(*it);
}

#include <ctime>
#define TIME std::time_t t = std::time(0); std::tm* now = std::localtime(&t);

int get_year   (void) { TIME; return (now->tm_year + 1900); }
int get_month  (void) { TIME; return (now->tm_mon  + 1   ); }
int get_day    (void) { TIME; return (now->tm_mday       ); }
int get_hour   (void) { TIME; return (now->tm_hour       ); }
int get_minute (void) { TIME; return (now->tm_min        ); }


void send_to_client(User u, std::string msg, size_t delay)
{
	send(u.getFd(), msg.c_str(), msg.length(), delay);
}

