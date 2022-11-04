/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_local_time.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:50:08 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 14:50:56 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <ctime>

#define TIME std::time_t t = std::time(0); std::tm* now = std::localtime(&t);

int get_year   (void) { TIME; return (now->tm_year + 1900); }
int get_month  (void) { TIME; return (now->tm_mon  + 1   ); }
int get_day    (void) { TIME; return (now->tm_mday       ); }
int get_hour   (void) { TIME; return (now->tm_hour       ); }
int get_minute (void) { TIME; return (now->tm_min        ); }
