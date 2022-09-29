/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:18:05 by thhusser          #+#    #+#             */
/*   Updated: 2022/09/29 12:50:07 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

// domaine AF_LOCAL communication precessus sur le meme hote
// tpe de communication SOCK_STREAM pour TCP
// protocole 0 pour internet protocole (IP)

int main() {
	if (TEST) {
		int fd;
		if (!(fd = socket(AF_LOCAL, SOCK_STREAM, 0))) {
			perror("Socket failled");
			exit(EXIT_FAILURE);
		}
		std::cout << _CYAN << "File descriptor socket : " << fd << _NC << std::endl;
	}
	return (0);
}