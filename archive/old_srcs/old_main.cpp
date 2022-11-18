0/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:18:05 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/03 14:12:08 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>
#include <typeinfo>
// domaine AF_LOCAL communication precessus sur le meme hote
// tpe de communication SOCK_STREAM pour TCP
// protocole 0 pour internet protocole (IP)

/*
struct sockaddr {
        ushort  sa_family;
        char    sa_data[14];
};

struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};
*/

int main() {

	if (TEST) {

		int fd = -1;
		int new_socket = -1;
		int valread = -1;

		int opt = 1;
		char buffer[2048] = {0};
		// char* hello;

		// hello = (char *)malloc(sizeof(char) * strlen(("Hello from server") + 1));
		// strcpy(hello, "Hello from server");
		struct sockaddr_in address;
		int addrlen = sizeof(address);

		/*
			short            sin_family;   // e.g. AF_INET
    		unsigned short   sin_port;     // e.g. htons(3490)
    		struct in_addr   sin_addr;     // see struct in_addr, below
    		char             sin_zero[8];  // zero this if you want to
		*/

		if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("Socket failled");
			exit(EXIT_FAILURE);
		}
		std::cout << _CYAN << "File descriptor socket : " << fd << _NC << std::endl;

		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
			perror("Setsockopt failled");
			exit(EXIT_FAILURE);
		}
		// Fonctionne pas avec AF_LOCAL
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
  		address.sin_port = htons(PORT);


		// cast de sockaddr_in en sockaddr
		if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
			perror("Bind failled");
			exit(EXIT_FAILURE);
		}
		//Definir le nombre max d'ecoute
		if (listen(fd, 3)) {
			perror("Listen failled");
			exit(EXIT_FAILURE);
		}
		for(;;) {
			if ((new_socket = accept(fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
				perror("accept");
				exit(EXIT_FAILURE);
			}
			valread = read(new_socket, buffer, 2048);
			printf("%s\n", buffer);
			buffer[0] = 0;
		}
		// send(new_socket, hello, strlen(hello), 0);
		// printf("Hello message sent\n");
		// closing the connected socket
		close(new_socket);
		// closing the listening socket
		shutdown(fd, SHUT_RDWR);
		// free(hello);
	}
	return (0);
}
