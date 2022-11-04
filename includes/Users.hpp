/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:48 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 14:59:28 by adlancel         ###   ########.fr       */
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
		
		std::string _ip;
		std::string _hostname;
		std::string _nickname;
		std::string _username;
		std::string _fullname;
		bool		_isKill;

	public:

		User(void);
		User(const int, std::string);
		User(const User &);
		User &operator=(const User &);
		~User( void );

		std::string getIp()			  const;
		int         getFd()           const;
		std::string getNickname()     const;
		void		setNickname(std::string);
		std::string getUsername()     const;
		void		setUsername(std::string);
		std::string getFullName()     const;
		void		setFullName(std::string);
		std::string getHostname()     const;
		void		setHostname(std::string);
		
		time_t      getTimeActivity() const;
		void        setTimeActivity();

		bool        getValidUser()    const;
		void        setValidUser(bool);

		void        setValidPasswd(bool);
		void        getValidPasswd() const;

		bool        getPingStatus()   const;
		void        setPingStatus(bool);

		bool		getIsKill()		  const;
		void		setIsKill(bool);

};
