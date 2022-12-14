#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>			// perror
#include <cstdlib>			// exit
#include <header.hpp>

// #define PORT 5555
 
int main(int argc, char const* argv[])
{
    (void)argv;
    (void)argc;
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;
	// char* hello;

	// hello = (char *)malloc(sizeof(char) * strlen(("Hello from client") + 1));
	// strcpy(hello, "Hello from client");
    // char buffer[1024] = { 0 };
    std::string buffer;
    while (std::getline(std::cin, buffer)) {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }
    
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
    
        // Convert IPv4 and IPv6 addresses from text to binary
        // form
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
            <= 0) {
            printf(
                "\nInvalid address/ Address not supported \n");
            return -1;
        }
        if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }

        send(sock, buffer.c_str(), buffer.size(), 0);
    }
    // valread = read(sock, buffer, 1024);
    // printf("%s\n", buffer);
 
    // closing the connected socket
    // close(client_fd);
    // free(hello);
    return 0;
}