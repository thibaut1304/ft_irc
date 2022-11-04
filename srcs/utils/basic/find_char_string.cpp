/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char_string.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:51:10 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 16:47:10 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

int findCharParsing(std::string buff) {
	std::vector<char> vec;
	// " ,*?!@$:.;"
	
	vec.push_back(' '); vec.push_back(','); vec.push_back('*'); vec.push_back('?');
	vec.push_back('!'); vec.push_back('@'); vec.push_back('$'); vec.push_back(':');
	vec.push_back('.'); vec.push_back(';');
	std::vector<char>::iterator it = vec.begin();
	for (; it != vec.end(); it++) {
		if (buff.find(*it) != size_t(-1))
			return (true);
	}
	return (false);
}