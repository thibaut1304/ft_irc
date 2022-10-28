/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/21 00:17:09 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <Header.hpp>
# include <Users.hpp>
# include <Client.hpp>

extern bool serverLife;

// class User;

class Server {
	private:
		
		Server(void);
		
		int					_fdServer;
		int					_fdPoll;
		fd_set 				_set;
		
		struct sockaddr_in	_serverAddress;
		struct sockaddr_in	_clientAddress;
		
		std::string			_passwd;	
		std::string			_port;

		// int					_nbUers;
		std::map<const int, Client>	_client;			// --> creer classe user pour ajouter les infos pour les connections
		std::map<int, User>	_user;
	public:

		Server(std::string, std::string);
		~Server(void);
		std::string getPasswd() const;			
		std::string getPort() const;
		void		setPasswd(std::string);
		void		setPort(std::string);

		void		init();		
		void		launch();
		int			newConnection(void);
		void		requestClient(struct epoll_event);

};

#endif