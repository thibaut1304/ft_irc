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
int get_seconds(void) { TIME; return (now->tm_sec        ); }

std::string get_charday(void) {
	TIME;
	int days_since_sunday = now->tm_wday;
	if (days_since_sunday == 0) return "Sun";
	if (days_since_sunday == 1) return "Mon";
	if (days_since_sunday == 2) return "Tue";
	if (days_since_sunday == 3) return "Wed";
	if (days_since_sunday == 4) return "Thu";
	if (days_since_sunday == 5) return "Fri";
	if (days_since_sunday == 6) return "Sat";
	else return "";
}
