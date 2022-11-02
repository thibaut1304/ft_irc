/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectionReplies.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:44:47 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 18:21:35 by thhusser         ###   ########.fr       */
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

# define ERR_ERRONEUSNICKNAME(nick) (" 432 * " + nick + " :Erroneous nickname" + "\r\n")
# define ERR_NONICKNAMEGIVEN(cmd) (" 431 * " + cmd + " :No nickname given" + "\r\n")
# define ERR_NICKNAMEINUSE(nick) (" 433 * " + nick + " :Nickname is already in use" + "\r\n")
// je sais pas ou l'assigner
# define ERR_NICKCOLLISION(nick, user, host) (" " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

# define ERR_UNKNOWNCOMMAND(nick, cmd) (" 421 " + nick + " " + cmd + " :Unknown command" + "\r\n")