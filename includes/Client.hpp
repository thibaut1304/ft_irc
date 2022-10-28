/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:43:29 by adlancel          #+#    #+#             */
/*   Updated: 2022/10/28 15:43:34 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header.hpp"

class Client {
public:
    Client(void);
    Client(const int fd, std::string &ip);
    Client &operator=(Client &other);
    ~Client();
    int get_fd();
    std::string get_ip();
    void append_buff(std::string buff);
    std::string get_buf();

private:
    const int _fd;
    std::string _ip;
    std::string buf;
    bool _is_ok;
    std::vector<std::string> cmd;
};
