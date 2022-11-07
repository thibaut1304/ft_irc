/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectionReplies.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:44:47 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/05 13:25:05 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// NAME == HOST
// Replies : HOST + CODE + NICK + MSG

#define PING(msg) ("PING " + msg + "\r\n")

/* ...................................................... */
/* .................. Accept connection ................. */
/* ...................................................... */

// 001
#define RPL_WELCOME(nick, user, host) (" :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n");
// 002
#define RPL_YOURHOST(servername, version) (" :Your host is " + servername + ", running version " + version + "\r\n");
// 003
#define RPL_CREATED(date) (" :This server was created " + date + "\r\n")
// 004
#define RPL_MYINFO(servername, version, userMode, channelMode) (" " + servername + " " + version + " " + userMode + " " + channelMode + "\r\n");

/* ...................................................... */
/* .................. Error Nick ........................ */
/* ...................................................... */

#define ERR_NONICKNAMEGIVEN(cmd) (" 431 * " + cmd + " :No nickname given" + "\r\n")
#define ERR_ERRONEUSNICKNAME(nick, text) (" 432 " + nick + " " + text + " :Erroneous nickname\r\n")
#define ERR_NICKNAMEINUSE(nick) (" 433 * " + nick + " :Nickname is already in use" + "\r\n")

// Uniquement pour une interface inter serveur
#define ERR_NICKCOLLISION(nick, user, host) (" " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

/* ...................................................... */
/* ................ Unknown command ..................... */
/* ...................................................... */

#define ERR_UNKNOWNCOMMAND(nick, cmd) (" 421 " + nick + " " + cmd + " :Unknown command" + "\r\n")

/* ...................................................... */
/* .................. Error User ........................ */
/* ...................................................... */

#define ERR_NEEDMOREPARAMS(cmd, nick) (" 461 " + nick + " " + cmd + " :Not enough parameters" + "\r\n")
#define ERR_ALREADYREGISTRED(nick) (" 462 " + nick + " :You may not reregister" + "\r\n")
#define ERR_USERNAMENOTVALID(cmd, nick) (" 468 " + nick + " " + cmd + " :Your username is not valid\r\n")
// :irc.local 468 * USER :Your username is not valid

/* ...................................................... */
/* .................. Error Ping ........................ */
/* ...................................................... */

#define ERR_NOORIGIN "409 :No origin specified" + "\r\n"

// # define ERR_NOSUCHSERVER NAME + "402 :No origin specified" + "\r\n"

#define ERR_NOTREGISTERED(cmd) (NAME + " 451 * " + cmd + " :You have not registered" + "\r\n")

/* ...................................................... */
/* ......... Reply for quit and timeout ................. */
/* ...................................................... */

#define REGISTRATION_TIMEOUT(name, ip) ("ERROR :Closink link: (" + name + "@" + ip + ") [Registration timeout]\r\n")
#define PING_TIMEOUT(username, ip) ("ERROR :Closink link: (" + username + "@" + ip + ") [Ping timeout: 120 seconds]\r\n")
#define CLIENT_EXIT(user, ip, msg) ("ERROR :Closing link: (" + user + "@" + ip + ") [" + msg + "]\r\n")

/* ...................................................... */
/* .................. Error join ........................ */
/* ...................................................... */
#define ERR_BADCHANMASK(nick, channel) (" 476 " + nick + " " + channel + " :Invalid channel name" \
		"\r\n");
/* ...................................................... */
/* ........................ wsz ......................... */
/* ...................................................... */

#define ERR_TEMPLATE(ERR_CODE, MSG) (std::string() + NAME + " " + ERR_CODE + " " + MSG + "\r\n")

#define ERR_NOSUCHSERVER(server_name)  ERR_TEMPLATE("402", server_name   + " " + ":No such server")
#define ERR_NOSUCHCHANNEL(server_name) ERR_TEMPLATE("403", server_name   + " " + ":No such channel")
#define ERR_UNKNOWNMODE(user,mode)     ERR_TEMPLATE("472", user+" "+mode + " " + ":is an unknown mode or character")

/* ...................................................... */
/* ....................... MOTD ......................... */
/* ...................................................... */

#define RPL_MOTDSTART(nick) (NAME + " 375 " + nick + " :" + NAME_V + " Message of the day - \r\n")
#define RPL_MOTD(nick, msg) (NAME + " 372 " + nick + " :" + msg + "\r\n")
#define RPL_ENDOFMOTD(nick) (NAME + " 376 " + nick + " :End of /MOTD command\r\n")

/* ...................................................... */
/* ..................... PASSWORD ....................... */
/* ...................................................... */

# define ERR_PASSWDMISMATCH(nick) (NAME + " 464 " + nick + " :Password incorrect\r\n")

/* ...................................................... */
/* ..................... PRIVMSG ........................ */
/* ...................................................... */

# define ERR_NOSUCHNICK(nick, client) (NAME + " 401 " + nick + " " + client + " :No such nick\r\n")
// 407     ERR_TOOMANYTARGETS "<target> :Duplicate recipients. No message
// 412     ERR_NOTEXTTOSEND ":No text to send"
// 301     RPL_AWAY "<nick> :<away message>"
// 414     ERR_WILDTOPLEVEL "<mask> :Wildcard in toplevel domain"
// 404     ERR_CANNOTSENDTOCHAN "<channel name> :Cannot send to channel"
// 413     ERR_NOTOPLEVEL "<mask> :No toplevel domain specified"
// 411     ERR_NORECIPIENT ":No recipient given (<command>)"

// :<c>!<1>@<172.17.0.1> PRIVMSG <b> :hello
