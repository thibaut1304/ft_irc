/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 06:14:30 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/11 06:17:25 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

void        __debug_modes            (Channel*    channel, std::string str);
bool        mode_check_arg_error     (Server*     server,  int arg_index, bool toggle);
bool        mode_is_in_charset       (std::string charset, char c);
bool        mode_get_sign            (std::string modes);
std::string mode_trim_sign           (std::string modes);
size_t      mode_str_to_num          (std::string arg);
bool        mode_is_invalid_password (Channel * channel, User user, std::string password, bool toggle);
bool        mode_is_missing_password (Channel * channel, User user, std::string password);

void mode_channel(Server* server, User user, std::string target);
void mode_user   (Server* server, User user, std::string target);


