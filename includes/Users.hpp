/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:48 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/01 14:47:02 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <Header.hpp>

class User {
	private:

		int         _fd;
		time_t      _time;
		bool        _statusPing;
		bool        _validUser;
		std::string _hostname;
		std::string _nickname;			// max 9 characters
		std::string _username;
		std::string _fullname;

	public:

		User(void);
		User(const int, std::string);
		User(const User &);
		User &operator=(const User &);
		~User( void );

		int         getFd()           const;
		std::string getNickname()     const;
		void		setNickname(std::string);
		std::string getUsername()     const;
		std::string getFullName()     const;
		std::string getHostname()     const;

		time_t      getTimeActivity() const;
		void        setTimeActivity();

		bool        getValidUser()    const;
		void        setValidUser(bool);

		bool        getPingStatus()   const;
		void        setPingStatus(bool);
};
