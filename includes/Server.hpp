/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/17 20:24:14 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <Header.hpp>
#include <Users.hpp>
#include <Channel.hpp>
#include <Commands.hpp>
#include <connectionReplies.hpp>

/* ========================================================================== */
/* --------------------------------- SERVER --------------------------------- */
/* ========================================================================== */

extern bool serverLife;
class Server
{
	public :
		/* .............................................. */
		/* .................. TYPEDEFS .................. */
		/* .............................................. */
		typedef std::string                   string;
		typedef std::map<string,Channel *>    map_channels;
		typedef std::pair<string,Channel *>   pair;
		typedef std::vector<string>           vector_string;
		typedef std::map<const int, User>     map_users;
		typedef std::map<std::string, User *> map_operators;

	private:

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


		/* .............................................. */
		/* ................ MEMBER VARS ................. */
		/* .............................................. */
		map_users     _users; // --> creer classe user pour ajouter les infos pour les connections
		map_operators _operators;
		map_channels  _channels;
		vector_string _allBuff;
		string        _buff;

		/* .............................................. */
		/* .................. METHODS ................... */
		/* .............................................. */

		/* CONSTRUCT / DESTRUCT ..... */
		/* .......................... */

	public:
		Server(void);
		Server(string, string);
		~Server(void);
		map_users     & get_users(void)     { return _users;     }
		map_operators & get_operators(void) { return _operators; }
		map_channels  & get_channels(void)  { return _channels;  }
		vector_string & get_allBuff(void)       { return _allBuff;   }
		string        & get_buff(void)          { return _buff;      }

		/* CORE ..................... */
		/* .......................... */
		void init           (void);
		void launch         (void);
		int  newConnection  (void);
		void requestClient  (struct epoll_event);
		void pingTime       (void);
		void cmdPing        (User,  string);
		void parse          (int);
		void killUserClient (int);
		void initCmd        (void);
		void acceptUser     (User);
		void exploreCmd     (int, std::string);

		void server_launch_start (int fdServer, int fdPoll, Server &server);

		/* USERS .................... */
		/* .......................... */
		map_users get_users (void) const;
		string    getPasswd ()     const;
		string    getPort   ()     const;
		void      setPasswd (string);
		void      setPort   (string);

		/* CHANNEL REQUESTS ......... */
		/* .......................... */
		map_channels getChannels        (void);
		map_users    getUsers           (void);
		User*        getUser            (string nickname);
		bool         does_channel_exist (string ch_name);
		Channel*     getChannel         (string ch_name);
		void         deleteChannel      (string ch_name);
		void         addChannel         (string ch_name, Channel::UserPtr user);

		/* OPERATORS ................ */
		/* .......................... */

		void           add_server_operator      (string user_nickname, string op_nickname);
		map_operators* get_server_operators     (void);
		bool           does_operator_name_exist (string name);
		bool           is_server_operator       (string nick);
		string         is_this_user_an_operator (string user_name);

		/* UTILS .................... */
		/* .......................... */
		void print_server_users(void);
};

/* ========================================================================== */
/* -------------------------- NON MEMBER FUNCTIONS -------------------------- */
/* ========================================================================== */

/* ...................................................... */
/* .................... SERVER INIT ..................... */
/* ...................................................... */
void server_init_socket_fd         (int *fd);
void server_init_socket_struct     (int fd, sockaddr_in &server_sock_struct, std::string port);
void server_init_bind_fd_to_socket (int fd, sockaddr_in &server_sock_struct);
void server_init_check             (int fd);

/* ...................................................... */
/* ................... SERVER LAUNCH .................... */
/* ...................................................... */
void server_launch_epoll_init        (int &fdPoll);
void server_launch_epoll_struct_init (int fdServer, int fdPoll);
void server_launch_start             (int fdServer, int fdPoll, Server &server);

/* ...................................................... */
/* ............... SERVER NEW CONNECTION ................ */
/* ...................................................... */
int  server_new_connection_accept    (int fdServer, sockaddr_in &clientAddress, int size);
void server_new_connection_epoll_ctl (int fdNew,    int fdPoll);

/* ...................................................... */
/* ....................... UTILS ........................ */
/* ...................................................... */
void splitCmdIrssi   (std::vector<std::string> &sCmd, std::string cmd);
void splitCmdUser    (std::vector<std::string> &sCmd, std::string cmd);
void splitCmd        (std::vector<std::string> &sCmd, std::string cmd);
void split           (std::vector<std::string> &sCmd, std::string cmd, std::string delimiter);
void print_buff      (std::vector<std::string> buff);
void myToupper       (std::string &emma);
void perror_and_exit (std::string code);
int  findCharParsing (std::string buff);
void send_to_client  (int fd, std::string msg, std::string err_code = "");


int         get_year    (void);
int         get_month   (void);
int         get_day     (void);
int         get_hour    (void);
int         get_minute  (void);
int         get_seconds (void);
std::string get_charday (void);

/* ...................................................... */
/* ....................... DEBUG ........................ */
/* ...................................................... */
void __debug_newConnection (std::string ip);
void __debug_requestClient (char *buff);
void __debug_exploreCmd    (void);
void __debug_unknown       (Server &serv); // TODO find corresponding method to debug

/* ------------------------------------------------------ */
/* -------------------- ERROR CHECKS -------------------- */
/* ------------------------------------------------------ */
bool check_ERR_NOSUCHSERVER   (Server * server, User user);
bool check_ERR_NOSUCHSERVER   (Server * server, User user);
bool check_ERR_NEEDMOREPARAMS (Server * server, User user);
bool check_ERR_NOTONCHANNEL   (Server * server, User user);
bool check_ERR_NOSUCHCHANNEL  (Server * server, User user);
bool check_ERR_NOTREGISTERED  (Server * server, User user);
bool check_ERR_NONICKNAMEGIVEN(Server * server, User user);
bool check_ERR_NOSUCHNICK     (Server * server, User user);




#endif
