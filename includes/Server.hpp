/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/14 16:02:12 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <Header.hpp>
#include <Users.hpp>
#include <Channel.hpp>
#include <Commands.hpp>
#include <sstream>

#include <connectionReplies.hpp>
#include <serverQueries.hpp>
#include <cerrno>

#include "Header_wsz.hpp"

/* ========================================================================== */
/* --------------------------------- SERVER --------------------------------- */
/* ========================================================================== */

extern bool serverLife;
class Server
{
	private:
		Server(void);

		int _fdServer;
		int _fdPoll;

		struct sockaddr_in _serverAddress;
		struct sockaddr_in _clientAddress;

		std::string _passwd;
		std::string _port;

		// int					_nbUers;
		std::map<int, std::string> _buffUsers;

		typedef void (*cmdFunc)(Server *, User );
		std::map<std::string, cmdFunc> _listCmd;

	public:
		/* .............................................. */
		/* .................. TYPEDEFS .................. */
		/* .............................................. */
		typedef std::string string;
		typedef std::map<string, Channel *> map_channels;
		typedef std::pair<string, Channel *> pair;
		typedef std::vector<string> vector_string;
		typedef std::map<const int, User> map_users;
		typedef std::map<std::string, User *> map_operators;

		/* .............................................. */
		/* ................ MEMBER VARS ................. */
		/* .............................................. */
		map_users _users; // --> creer classe user pour ajouter les infos pour les connections
		map_operators _operators;
		map_channels _channels;
		vector_string _allBuff;
		string _buff;

		/* .............................................. */
		/* .................. METHODS ................... */
		/* .............................................. */
		Server(string, string);
		~Server(void);

		map_users get_users(void) const;
		string getPasswd() const;
		string getPort() const;
		void setPasswd(string);
		void setPort(string);

		void init(void);
		void launch(void);
		int newConnection(void);
		void requestClient(struct epoll_event);
		void pingTime(void);
		void server_launch_start(int fdServer, int fdPoll, Server &server);
		void cmdPing(User, string);
		void parse(int);
		void killUserClient(int);

		void initCmd();
		void acceptUser(User);
		void exploreCmd(int, std::string);

		/* .............................................. */
		/* .............. CHANNEL REQUESTS .............. */
		/* .............................................. */
		bool does_channel_exist(string ch_name);
		Channel *getChannel(string ch_name);
		std::map<std::string, Channel *> getChannels();
		std::map<const int, User> getUsers();
		User *getUser(std::string nickname);
		void deleteChannel(string ch_name);
		void addChannel(string ch_name, Channel::UserPtr user);


		/* .............................................. */
		/* .................... wsz ..................... */
		/* .............................................. */

		map_operators * get_server_operators(void) {return &_operators; }

		void add_server_operator(std::string nickname)
		{
			User * user = getUser(nickname);
			map_operators * operators = get_server_operators();
			std::pair<std::string, User *> p(nickname, user);
			operators->insert(p);
		}

		bool is_server_operator(std::string nick)
		{
			User * user = getUser(nick);
			map_operators * operators = get_server_operators();
			map_operators::iterator it = operators->begin();
			map_operators::iterator ite = operators->end();

			while (it != ite)
			{
				if (it->second == user)
					return (true);
				it++;
			}
			return false;
		}

		void print_server_users(void)
		{
			map_users::iterator it = _users.begin();
			map_users::iterator ite = _users.end();
			int fd;
			while (it != ite)
			{
				fd = (*it).second.getFd();
				std::cout << "+ FD OF SERVER USER IS : " << fd << std::endl;
				std::cout << "- FD OF SERVER USER IS : " << (*it).first << std::endl;
				it++;
			}
		}

};

/* ========================================================================== */
/* -------------------------- NON MEMBER FUNCTIONS -------------------------- */
/* ========================================================================== */

/* ...................................................... */
/* .................... SERVER INIT ..................... */
/* ...................................................... */
void server_init_socket_fd(int *fd);
void server_init_socket_struct(int fd, sockaddr_in &server_sock_struct, std::string port);
void server_init_bind_fd_to_socket(int fd, sockaddr_in &server_sock_struct);
void server_init_check(int fd);

/* ...................................................... */
/* ................... SERVER LAUNCH .................... */
/* ...................................................... */
void server_launch_epoll_init(int &fdPoll);
void server_launch_epoll_struct_init(int fdServer, int fdPoll);
void server_launch_start(int fdServer, int fdPoll, Server &server);

/* ...................................................... */
/* ............... SERVER NEW CONNECTION ................ */
/* ...................................................... */
int server_new_connection_accept(int fdServer, sockaddr_in &clientAddress, int size);
void server_new_connection_epoll_ctl(int fdNew, int fdPoll);

/* ...................................................... */
/* ....................... UTILS ........................ */
/* ...................................................... */
void splitCmdIrssi(std::vector<std::string> &sCmd, std::string cmd);
void splitCmdUser(std::vector<std::string> &sCmd, std::string cmd);
void splitCmd(std::vector<std::string> &sCmd, std::string cmd);
void split(std::vector<std::string> &sCmd, std::string cmd, std::string delimiter);
void print_buff(std::vector<std::string> buff);
void myToupper(std::string &emma);
void perror_and_exit(std::string code);
int findCharParsing(std::string buff);


int get_year(void);
int get_month(void);
int get_day(void);
int get_hour(void);
int get_minute(void);
int get_seconds(void);
std::string get_charday(void);

/* ...................................................... */
/* ....................... DEBUG ........................ */
/* ...................................................... */
void __debug_newConnection(std::string ip);
void __debug_requestClient(char *buff);
void __debug_exploreCmd(void);
void __debug_unknown(Server &serv); // TODO find corresponding method to debug

#endif
