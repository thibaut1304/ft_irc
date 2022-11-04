/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverQueries.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:03:48 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/03 19:53:37 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define ERR_TEMPLATE(ERR_CODE, MSG) (std::string () + ERR_CODE + " " + MSG + "\r\n")

# define ERR_NOSUCHSERVER(server_name) ERR_TEMPLATE("402", server_name + " :No such server")

