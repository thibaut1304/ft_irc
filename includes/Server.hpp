/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 15:52:03 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <Header.hpp>
# include <Users.hpp>
# include <Commands.hpp>
# include <sstream>


# include <connectionReplies.hpp>
# include <serverQueries.hpp>
# include "Header_wsz.hpp"

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

        typedef void (*cmdFunc)(Server *,User);
		std::map<std::string, cmdFunc>	_listCmd;
	

	public:
		std::map<const int, User>	_users;			// --> creer classe user pour ajouter les infos pour les connections
		std::vector<std::string>	_allBuff;
		std::string					_buff;

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
		void 		server_launch_start (int fdServer, int fdPoll, Server      & server);
		void		cmdPing(User, std::string);
		void		parse(int);
		void		killUserClient(int);

		void		initCmd();

		void 		acceptUser(User);
		void		exploreCmd(int, std::string);

};

void server_init_socket_fd           (int *fd);
void server_init_socket_struct       (int fd, sockaddr_in & server_sock_struct, std::string port);
void server_init_bind_fd_to_socket   (int fd, sockaddr_in & server_sock_struct);
void server_init_check               (int fd);

void server_launch_epoll_init        (int & fdPoll);
void server_launch_epoll_struct_init (int fdServer, int fdPoll);
void server_launch_start             (int fdServer, int fdPoll, Server      & server);

int server_new_connection_accept     (int fdServer, sockaddr_in & clientAddress, int size);
void server_new_connection_epoll_ctl (int fdNew, int fdPoll);

void splitCmdIrssi                   (std::vector<std::string> & sCmd, std::string cmd);
void splitCmdUser                    (std::vector<std::string> & sCmd, std::string cmd);
void splitCmd                        (std::vector<std::string> & sCmd, std::string cmd);
void split                      	 (std::vector<std::string> & sCmd, std::string cmd, std::string delimiter);
void print_buff                      (std::vector<std::string> buff);
void myToupper                       (std::string & emma);

int get_year   (void);
int get_month  (void);
int get_day    (void);
int get_hour   (void);
int get_minute (void);

void send_to_client(int fd, std::string msg, std::string err_code = "");

void __debug_newConnection(std::string ip);
void __debug_requestClient(char *buff);
void __debug_exploreCmd   (void);
void   __debug_unknown(Server & serv); // TODO find corresponding method to debug

#endif
