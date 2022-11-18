/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:21:47 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/05 13:21:00 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <iomanip>

std::string 	citation() {
	std::vector<std::string> vec;
	srand(time(NULL));

	int val = rand() % 14 + 0;
	vec.push_back("Charity begins at home.");
	// (Charité bien ordonnée commence par soi-même.)
	vec.push_back("Might makes right.");
	// (La raison du plus fort est toujours la meilleure.)
	vec.push_back("No news is good news.");
	// (Pas de nouvelles, bonnes nouvelles.)
	vec.push_back("Practice makes perfect.");
	// (C'est en forgeant qu'on devient forgeron.)
	vec.push_back("You reap what you sow.");
	// (Qui sème le vent récolte la tempête.)
	vec.push_back("The grass is always greener on the other side of the fence.");
	// (L'herbe est plus verte ailleurs.)
	vec.push_back("All good things must come to an end!");
	// (Toutes les bonnes choses ont une fin !)
	vec.push_back("Better late than never.");
	// (Mieux vaut tard que jamais.)
	vec.push_back("Don't put the cart before the horse.");
	// (Il ne faut pas mettre la charrue avant les boeufs.)
	vec.push_back("A picture is worth a thousand words.");
	// (Une image vaut mille mots.)
	vec.push_back("Don't put all your eggs in one basket.");
	// (Il ne faut pas mettre tous ses oeufs dans le même panier.)
	vec.push_back("You can't have your cake and eat it too.");
	// (On ne peut pas avoir le beurre et l'argent du beurre.)
	vec.push_back("Might makes right.");
	// (Deux précautions valent mieux qu'une.)
	vec.push_back("Don't judge a book by its cover.");
	// (Ne jugez pas un livre à sa couverture.)
	vec.push_back("Old habits die hard.");
	// (Les habitudes ont la vie dure.)
	return (vec[val]);
}

void	motd(Server *serv, User user) {
	std::stringstream s;

	s << std::setw(50) << citation();
	if (user.getValidUser() == false) {
		std::string msg = ERR_NOTREGISTERED(print_cmd(serv->get_buff()));
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
	else if (user.getValidUser() == true && serv->get_buff().size() > 1) {
		return ;
	}
	else {
		std::string msg = RPL_MOTDSTART(user.getNickname());
		msg += RPL_MOTD(user.getNickname(), std::string("+-------------------------------------------------------------+"));
		msg += RPL_MOTD(user.getNickname(), s.str());
		msg += RPL_MOTD(user.getNickname(), std::string("+-------------------------------------------------------------+"));
		msg += RPL_ENDOFMOTD(user.getNickname());
		send(user.getFd(), msg.c_str(), msg.length(), 0);
	}
}
