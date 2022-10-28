/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:43:14 by adlancel          #+#    #+#             */
/*   Updated: 2022/10/28 15:43:19 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>
#include "Split.cpp"

Client::Client(void) : _fd(0), _ip(""), buf(""),  _is_ok(false), cmd()
{
    std::cout << "new client" << std::endl;
}
Client::Client(const int fd, std::string &ip) : _fd(fd), _ip(ip), buf(""), _is_ok(false), cmd()
{
    std::cout << "on fd = " << fd << "new client with ip = " << ip << std::endl;
}
Client::~Client()
{
}
int Client::get_fd()
{
    return _fd;
}
std::string Client::get_ip()
{
    return _ip;
}

void Client::append_buff(std::string buff)
{

    buf.append(buff);
    std::cout << "buff = " << buf << std::endl;
    //PARSE buffer et insert dans le vec command si command ok, if PASS/USER/NICK ok, is_ok passe a true et user créé 
};
std::string Client::get_buf()
{
    return (buf);
};
