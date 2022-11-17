/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:51:14 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/17 20:11:28 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

void cmdHelp(Server *serv, User user, std::vector<std::string> cmd) {
	(void)serv;
	int i = 1;
	std::stringstream s;
	std::string msg = "Lists of commands\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);

	std::vector<std::string>::iterator it_cmd = cmd.begin();
	for (;it_cmd != cmd.end(); it_cmd++) {
		s.str("");
		s << i;
		i++;
		std::string msg_cmd = s.str() + "\t- " + *it_cmd;
		send(user.getFd(), msg_cmd.c_str(), msg_cmd.length(), 0);
	}
}

void cmdMetro(Server *serv, User user, std::vector<std::string> cmd) {
	(void)cmd;
	(void)serv;
	std::string msg = "Look your phone ! 📱\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);
}

void bot(Server *serv, User user, std::vector<std::string> cmd) {
	(void)cmd;
	(void)serv;
	std::string msg = "I am a very intelligent bot but a little lazy I admit\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);
}

void cmdWeather(Server *serv, User user, std::vector<std::string> cmd) {
	(void)cmd;
	(void)serv;
	std::string msg = "About 25 degrees 🌞\r\n";
	send(user.getFd(), msg.c_str(), msg.length(), 0);
}

void cmdTime(Server *serv, User user, std::vector<std::string> cmd) {
	(void)cmd;
	(void)serv;
	std::string          msg;
	std::stringstream    server_time;

		server_time        \
			<< get_charday() \
			<< " " \
			<< ((get_day() < 10) ? "0" : "") \
			<< get_day()   \
			<< "/"         \
			<< ((get_month() < 10) ? "0" : "") \
			<< get_month() \
			<< "/"         \
			<< get_year()  \
			<< " "         \
			<< get_hour()  \
			<< ":"         \
			<< ((get_minute() < 10) ? "0" : "") \
			<< get_minute() \
			<< ":"         \
			<< ((get_seconds() < 10) ? "0" : "") \
			<< get_seconds() \
			<< " CET"
			<< std::endl;

		msg =  NAME_V;
		msg += " ";
		msg += ":";
		msg += server_time.str();
		send(user.getFd(), msg.c_str(), msg.length(), 0);
}

void	initCmdBot(std::map<std::string, cmdBot> & listCmd) {
	listCmd["HELP"] = &cmdHelp;
	listCmd["BOT"] = &bot;
	listCmd["M14"] = &cmdMetro;
	listCmd["WEATHER"] = &cmdWeather;
	listCmd["TIME"] = &cmdTime;

}

void	initStringCmd(std::vector<std::string> & cmd) {
	cmd.push_back("HELP : This help text\r\n");
	cmd.push_back("M14 : Know the timetables of the metro 14\r\n");
	cmd.push_back("BOT : A short description about me\r\n");
	cmd.push_back("WEATHER : The weather report\r\n");
	cmd.push_back("TIME : Print the time\r\n");
}

void executeBot(Server *serv, User user) {
	std::vector<std::string> recordCmd;
	initStringCmd(recordCmd);

	std::vector<std::string> allBuff = serv->_allBuff;
	allBuff.erase(allBuff.begin());
	std::string cmd = print_allBuff(allBuff);
	myToupper(cmd);

	std::map<std::string, cmdBot> listCmd;
	initCmdBot(listCmd);
	std::map<std::string, cmdBot>::iterator it_list = listCmd.find(cmd);

	if (it_list != listCmd.end())
		it_list->second(serv, user, recordCmd);
	else {
		std::string msg_error = "This command does not exist\r\n";
		send(user.getFd(), msg_error.c_str(), msg_error.length(), 0);
		cmdHelp(serv, user, recordCmd);
	}
}
