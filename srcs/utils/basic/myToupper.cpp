/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myToupper.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:45:45 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 14:46:01 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void		myToupper(std::string & emma) {
	std::string::iterator	it = emma.begin();

	for (; it != emma.end();it++)
		*it = std::toupper(*it);
}
