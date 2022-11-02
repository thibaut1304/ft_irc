/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:51:27 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/02 15:15:01 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void	cap(Server *serv, User user) {
#if DEBUG == 1
	std::cout << _CYAN << "CMD CAP" << _NC << std::endl;
#endif
	(void)serv;
	(void)user;
	return ;
}