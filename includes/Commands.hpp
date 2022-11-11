/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:29:55 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 18:23:17 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class Server;
class User;

std::string	print_allBuff(std::vector<std::string>);
std::string print_cmd(std::vector<std::string> buff);

void cap          (Server *, User);


// # REGISTRATION
void pass          (Server *, User);
void nick          (Server *, User);
void user          (Server *, User);
void server        (Server *, User);
void oper          (Server *, User);
void quit          (Server *, User);
void squit         (Server *, User);

// # CHANNEL OPERATIONS
void join          (Server *, User);
void part          (Server *, User);
void mode          (Server *, User);
void channel_modes (Server *, User); // TODO wtf?
void user_modes    (Server *, User); // TODO wtf?
void topic         (Server *, User);
void names         (Server *, User);
void list          (Server *, User);
void invite       (Server *, User);
void kick          (Server *, User);

// # SERVER QUERIES AND COMM,NDS
void version       (Server *, User);
void stats         (Server *, User);
void links         (Server *, User);
void time          (Server *, User);
void connect       (Server *, User);
void trace         (Server *, User);
void admin         (Server *, User);
void info          (Server *, User);

// # SENDING MESSAGES
void privmsg       (Server *, User);
void notice        (Server *, User);

// # USER BASED QUERIES
void who           (Server *, User);
void whois         (Server *, User);
void whowas        (Server *, User);

// # MISC MESSAGES
void kill          (Server *, User);
void ping          (Server *, User);
void pong          (Server *, User);
void error         (Server *, User);

// # OPTIONAL MESSAGES
void away          (Server *, User);
void rehash        (Server *, User);
void restart       (Server *, User);
void summon        (Server *, User);
void users         (Server *, User);
void wallops       (Server *, User);
void userhost      (Server *, User);
void ison          (Server *, User);
void motd          (Server *, User);

