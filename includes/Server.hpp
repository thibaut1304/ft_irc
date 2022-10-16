/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:12 by thhusser          #+#    #+#             */
/*   Updated: 2022/10/16 20:32:08 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <Header.hpp>

extern bool serverLife;

class Server {
	private:
		
		std::string	_passwd;	
		std::string	_port;
	
	public:

		Server(void);
		Server(std::string, std::string);
		~Server(void);
		std::string getPasswd() const;			
		std::string getPort() const;
		void		setPasswd(std::string);
		void		setPort(std::string);

		void		launch();		
};

#endif