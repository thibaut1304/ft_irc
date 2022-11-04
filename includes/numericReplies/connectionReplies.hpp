/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectionReplies.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:44:47 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 17:11:53 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// NAME == HOST
// Replies : HOST + CODE + NICK + MSG

# define PING(msg)   ("PING " + msg + "\r\n")

/* ...................................................... */
/* .................. Accept connection ................. */
/* ...................................................... */

// 001
# define RPL_WELCOME(nick, user, host) 	(" :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n");
// 002
# define RPL_YOURHOST(servername, version) (" :Your host is " + servername + ", running version " + version + "\r\n");
// 003
# define RPL_CREATED(date) (" :This server was created " + date + "\r\n")
// 004
# define RPL_MYINFO(servername, version, userMode, channelMode) (" " + servername + " " + version + " " + userMode + " " + channelMode + "\r\n"); 

/* ...................................................... */
/* .................. Error Nick ........................ */
/* ...................................................... */

# define ERR_NONICKNAMEGIVEN(cmd)   (" 431 * " + cmd  + " :No nickname given"          + "\r\n")
# define ERR_ERRONEUSNICKNAME(nick) (" 432 * " + nick + " :Erroneous nickname"         + "\r\n")
# define ERR_NICKNAMEINUSE(nick)    (" 433 * " + nick + " :Nickname is already in use" + "\r\n")

// Uniquement pour une interface inter serveur
# define ERR_NICKCOLLISION(nick, user, host) (" " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

/* ...................................................... */
/* ................ Unknown command ..................... */
/* ...................................................... */

# define ERR_UNKNOWNCOMMAND(nick, cmd) (" 421 " + nick + " " + cmd + " :Unknown command" + "\r\n")

/* ...................................................... */
/* .................. Error User ........................ */
/* ...................................................... */

# define ERR_NEEDMOREPARAMS(cmd, nick) (" 461 " + nick + " " + cmd + " :Not enough parameters" + "\r\n")
# define ERR_ALREADYREGISTRED(nick) (" 462 " + nick + " :You may not reregister" + "\r\n")

/* ...................................................... */
/* .................. Error Ping ........................ */
/* ...................................................... */

# define ERR_NOORIGIN "409 :No origin specified" + "\r\n"

// # define ERR_NOSUCHSERVER NAME + "402 :No origin specified" + "\r\n"

# define ERR_NOTREGISTERED(cmd) (NAME + " 451 * " + cmd + " :You have not registered" + "\r\n")

/* ...................................................... */
/* ......... Reply for quit and timeout ................. */
/* ...................................................... */

/* ...................................................... */
/* .................. Error join ........................ */
/* ...................................................... */
# define ERR_BADCHANMASK(nick, channel) (" 476 " + nick + " " + channel + " :Invalid channel name""\r\n");
/* ...................................................... */
/* ...................................................... */
/* ...................................................... */
/* ...................................................... */

# define REGISTRATION_TIMEOUT(name, ip) ("ERROR :Closink link: (" + name + "@" + ip + ") [Registration timeout]\r\n")
// ERROR :Closing link: (811AAAAAC@172.17.0.1) [Registration timeout]  -> 60s

# define PING_TIMEOUT(username, ip) ("ERROR :Closink link: (" + username + "@" + ip + ") [Ping timeout: 120 seconds]\r\n")
// ERROR :Closing link: (1@172.17.0.1) [Ping timeout: 120 seconds]  -> une fois connecte

# define CLIENT_EXIT(user, ip, msg) ("ERROR :Closing link: (" + user + "@" + ip + ") [" + msg + "]\r\n")
// quit
// ERROR :Closing link: (1@172.17.0.1) [Client exited]  --> 1 = username sinon a definir