/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:58:13 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/02 15:04:19 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	pass(Server *serv, User user) {
#if DEBUG
	std::cout << _CYAN << "CMD PASS" << _NC << std::endl;
#endif
	(void)serv;
	(void)user;
	return ;
}