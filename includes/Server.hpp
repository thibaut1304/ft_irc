/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 17:50:09 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <Header.hpp>
# include <utils.hpp>
# include <Users.hpp>
# include <commands.hpp>


# include <connectionReplies.hpp>

# include <cerrno>


// Structure de commande a faire pour le parsing et le traitement !

/*
	struct s_commande {
		std::vector<std::string>	buffAll;
		std::string					commande;
		int 						nbCommand;
	}; 
*/

extern bool serverLife;

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

		std::map<int, std::string>	_buffUsers;

        typedef void (*cmdFunc)(Server *,User);
		std::map<std::string, cmdFunc>	_listCmd;
		
		std::map<const int, User>	_users;
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
		void		parse(int);
		void		killUserClient(User);

		void		initCmd();

		void 		acceptUser(User);
		void		exploreCmd(int, std::string);

		/*******************************/
		/************ TRASH ************/
		/*******************************/
		// void		pingTime();
		// void		cmdPing(User, std::string);
};

#endif
