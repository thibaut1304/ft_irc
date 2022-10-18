/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:48 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/18 18:23:45 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <Header.hpp>

class User {
	private:
	
		const int 	_fd;
		std::string					_hostname;
		std::string					_nickname;			// max 9 characters
		std::string					_username;			
		std::string 				_fullname;

	public:
		
		User(void);
		User(const int, std::string);
		User(const User &);
		User &operator=(const User &);
		~User( void );

		int		getFd() const;		
		std::string		getNickname() const;		
		std::string		getUsername() const;		
		std::string		getFullName() const;		
		std::string		getHostname() const;		
};