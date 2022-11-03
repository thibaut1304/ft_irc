/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:19:04 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/03 19:47:22 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEADER_HPP
# define _HEADER_HPP

# define Debug     1
# define MAX_USERS 10
# define BUFF_SIZE 4096

# include <string>

# define PING_TIME 5
# define PONG_TIME 20


# define NAME    std::string(":ft_irc.local")
# define VERSION std::string("0.2")
# define NAME_V  std::string("ft_irc.local")
# define DATE    std::string("30/10/2022")

# define _NC     "\033[0;0m"
# define _RED    "\033[0;31m"
# define _GREEN  "\033[0;32m"
# define _YELLOW "\033[0;33m"
# define _BLUE   "\033[0;34m"
# define _PURPLE "\033[0;95m"
# define _CYAN   "\033[0;36m"
# define _WHITE  "\033[0;37m"

# include <algorithm>    // std::transform
# include <cctype>

# include <iostream>
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

#endif
