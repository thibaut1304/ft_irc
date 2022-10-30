/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:29:55 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/30 17:02:43 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Server;
class User;

void	ping(Server *, User);
void	kill(Server *, User);