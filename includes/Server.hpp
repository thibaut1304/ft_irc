/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 13:14:55 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <Header.hpp>
# include <Users.hpp>
# include <commands.hpp>


# include <connectionReplies.hpp>
# include <connectionReplies.hpp>

# include <cerrno>


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
		std::map<int, std::string>	_buffUsers;

        typedef void (*cmdFunc)(Server *, User);
		std::map<std::string, cmdFunc>	_listCmd;
		
	public:
		std::map<const int, User>	_users;			// --> creer classe user pour ajouter les infos pour les connections

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
		void		pingTime();
		void		cmdPing(User, std::string);
		void		parse(int);
		void		killUserClient(User);

		void		initCmd();

		void 		acceptUser(User);
		void		exploreCmd(int, std::string);

};

#endif
