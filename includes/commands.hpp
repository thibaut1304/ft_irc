/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:29:55 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 15:59:41 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Server;
class User;

std::string	print_allBuff(std::vector<std::string>);
std::string print_cmd(std::vector<std::string> buff);

void	ping(Server *, User);
void	kill(Server *, User);
void	nick(Server *, User);