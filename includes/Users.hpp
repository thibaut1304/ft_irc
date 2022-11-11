/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:48 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/04 23:38:24 by thhusser         ###   ########.fr       */
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

		bool _receive_wallops;
		bool _receive_server_notice;
		bool _is_invisible;
		bool _is_operator;

		std::string _ip;
		std::string _hostname;
		std::string _nickname;
		std::string _username;
		std::string _fullname;
		std::string _PASS;
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
		std::string getPASS() 	      const;
		void 		setPASS(std::string);

		time_t      getTimeActivity() const;
		void        setTimeActivity();

		bool        getValidUser()    const;
		void        setValidUser(bool);

		bool        getPingStatus()   const;
		void        setPingStatus(bool);

		bool		getIsKill()		  const;
		void		setIsKill(bool);


		bool get_receive_wallops       (void) const;
		bool get_receive_server_notice (void) const;
		bool get_is_invisible          (void) const;
		bool get_is_operator           (void) const;
		void set_receive_wallops       (bool) ;
		void set_receive_server_notice (bool) ;
		void set_is_invisible          (bool) ;
		void set_is_operator           (bool) ;

};
