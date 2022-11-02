/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:48 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/31 13:57:21 by thhusser         ###   ########.fr       */
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
		bool		_passwd;
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
		std::string getUsername()     const;
		std::string getFullName()     const;
		std::string getHostname()     const;

		time_t      getTimeActivity() const;
		void        setTimeActivity();

		bool        getValidUser()    const;
		void        setValidUser(bool);

		void        setValidPasswd(bool);
		void        getValidPasswd() const;

		bool        getPingStatus()   const;
		void        setPingStatus(bool);

		void		setNickname(std::string nick);

};
