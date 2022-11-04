/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buff.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:51:34 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 14:51:42 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	print_buff(std::vector<std::string> buff) {
	std::vector<std::string>::iterator it = buff.begin();
	for (int i = 1;it != buff.end();it++, i++) {
		std::cout << "LIGNE : " << i << " " <<_RED << *it << _NC << std::endl;
	}
}
