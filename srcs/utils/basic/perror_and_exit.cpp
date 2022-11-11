/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_and_exit.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:25:23 by adlancel          #+#    #+#             */
/*   Updated: 2022/11/11 16:25:24 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Header.hpp>

void perror_and_exit(std::string code)
{
	std::string error = "Error send msg ";
	error.append(code);
	perror(error.c_str());
	exit(errno);
}
