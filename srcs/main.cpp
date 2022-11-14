/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:49 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/17 09:15:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

bool serverLife = true;

void	killCmd(int sig) {
	(void)sig;
	
#if Debug
	std::cout << _RED << "\nSignal : " << sig << _NC;
#endif

	std::cout << "\nServer killed" << std::endl;
	serverLife = false;
}

int	main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << _RED << "Error Usage : ./ft_irc <port> <password>" << _NC << std::endl;
		return (1);
	}
	Server server(argv[2], argv[1]);
	signal(SIGINT, killCmd);

#if Debug
	std::cout << "Port     : " << _YELLOW << server.getPort() << _NC << std::endl;
	std::cout << "Password : " << _YELLOW << server.getPasswd() << _NC << std::endl;
#endif


	server.init(); // Init server : create sockets, set socket options
	server.launch();

	Server::map_channels ch = server.getChannels();
	Server::map_channels::iterator it = ch.begin();
	Server::map_channels::iterator ite = ch.end();
	while (it != ite)
	{
		delete it->second;
		it++;
	}

	return (0);
}
