/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericsReplies.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:41:33 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/29 19:02:58 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define RPL_WELCOME(nick, user, host) 	("Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n");

# define RPL_YOURHOST(servername, version) ("Your host is " + servername + ", running version " + version + "\r\n");

# define RPL_CREATED(date) ("This server was created " + date + "\r\n")

# define RPL_MYINFO(servername, version, userMode, channelMode) (servername + " " + version + " " + userMode + " " + channelMode); 