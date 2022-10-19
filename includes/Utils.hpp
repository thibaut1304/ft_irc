/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:31:06 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/19 17:39:58 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Server.hpp>

void  splitCmds(std::vector<std::string> cmd_strings, std::vector<Command> *cmds);
std::vector<std::string>  splitBy(std::string str, const std::string &delimiter, std::string *buffer);
void	displayCommands(std::vector<Command> cmds);