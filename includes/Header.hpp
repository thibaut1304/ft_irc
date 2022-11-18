/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:19:04 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/18 11:08:46 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEADER_HPP
# define _HEADER_HPP

# define Debug     0
# define MAX_USERS 10
# define BUFF_SIZE 4096

# include <string>

# define REGIS_TIME 60  // 60
# define PING_TIME 120  // 120

# define REFRESH_DELAY 128 // Refresh rate in ms

# define VERSION std::string("0.5")
# define NAME_V  std::string("ircserv.local")
# define NAME    std::string(":ircserv.local")
# define DATE    std::string("30/10/2022")

# define SERVER_LOGIN    "%"
# define SERVER_PASSWORD "****"

# define _NC     "\033[0;0m"
# define _RED    "\033[0;31m"
# define _GREEN  "\033[0;32m"
# define _YELLOW "\033[0;33m"
# define _BLUE   "\033[0;34m"
# define _PURPLE "\033[0;95m"
# define _CYAN   "\033[0;36m"
# define _WHITE  "\033[0;37m"

// WSZ
# define STR_      std::string
# define VEC_      std::vector
# define BUFFER_   std::vector<std::string>
# define OK_       1
# define NOT_OK_   0
// WSZ END

# include <algorithm>    // std::transform
# include <cctype>

# include <iostream>
# include <sstream>
# include <cstdio>				// perror
# include <cstdlib>				// exit
# include <sys/socket.h>		// socket && bind
# include <netinet/in.h>		// struct sockaddr_in && htons
# include <unistd.h>			// read && close && sysconf
# include <string.h>
# include <signal.h>
# include <sys/select.h>		// select
# include <stdlib.h>
# include <arpa/inet.h>			// inet_ntoa
# include <sys/epoll.h>
# include <memory>
# include <map>
# include <vector>
# include <set>
# include <cerrno>

#endif
