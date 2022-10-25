#include <iostream>
#include <cstdio>       // perror
#include <cstdlib>      // exit
#include <sys/socket.h> // socket && bind
#include <netinet/in.h> // struct sockaddr_in && htons
#include <unistd.h>     // read && close && sysconf
#include <string.h>
#include <signal.h>
#include <sys/select.h> // select
#include <stdlib.h>
#include <arpa/inet.h> // inet_ntoa
#include <sys/epoll.h>
#include <memory>
#include <map>
#include <vector>

#define SERVER_PORT 18000
#define MAX_SIZE 4096

std::string bin2hex(int *input, size_t len)
{
    std::string result;
    std::string hex = "0123456789ABCDEF";

    if (input == NULL || len <= 0)
        return (NULL);

    int result_len = (len * 3) + 1;
    for (int i = 0; i < len; i++)
    {
        result[i * 3] = hex[input[i] >> 4];
        result[(i * 3) + 1] = hex[input[i] & 0x0F];
        result[(i * 3) + 2] = ' ';
    }
    return (result);
}
int main()
{

    for (int i = 0; i < 20; i++)
        close(i);
    int sockfd, connfd, n;
    int buff[MAX_SIZE + 1];
    int recvline[MAX_SIZE + 1];
    struct sockaddr_in servaddr;
    struct sockaddr_in _clientAdress;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if ((bind(sockfd, (sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        return (4);
    if ((listen(sockfd, 10)) < 0)
        return (2);

    for (;;)
    {
        struct sockaddr_in servaddr;
        socklen_t addr_len;

        std::cout << "Waiting for connections on port " << SERVER_PORT << std::endl;
        connfd = accept(sockfd, (sockaddr *)NULL, NULL);

        memset(recvline, 0, MAX_SIZE);

        while ((n = read(connfd, recvline, MAX_SIZE - 1) > 0))
        {
            // std::cout << bin2hex(recvline, n) << recvline << std::endl;

            if (recvline[n - 1] == '\n')
                break;
            memset(recvline, 0, MAX_SIZE);
        }
        if (n < 0)
            return (3);
        snprintf((char *)buff, sizeof(buff), "OK 200");
        write(connfd, (char *)buff, strlen((char *)buff));
        close(connfd);
    }
    // close(sockfd);
    return (0);
}
