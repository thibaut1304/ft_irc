/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:19:04 by thhusser          #+#    #+#             */
/*   Updated: 2022/09/29 15:21:18 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEADER_HPP
# define _HEADER_HPP

# define _NC "\033[0;0m"
# define _RED "\033[0;31m"
# define _GREEN "\033[0;32m"
# define _YELLOW "\033[0;33m"
# define _BLUE "\033[0;34m"
# define _PURPLE "\033[0;95m"
# define _CYAN "\033[0;36m"
# define _WHITE "\033[0;37m"

#include <iostream>
#include <cstdio>			// perror
#include <cstdlib>			// exit
#include <sys/socket.h>		// socket && bind
#include <netinet/in.h>		// struct sockaddr_in && htons
#include <unistd.h>			// read && close
#include <string.h>

#if TEST
# define PORT 5555
# define TRUE 1
#else
# define PORT "Not mode test"
# define TRUE "Not mode test"
#endif

#endif