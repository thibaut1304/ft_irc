// PING -> PONG
void	Server::cmdPing(User user, std::string hello) {
	std::string msg = PING(hello);
#if Debug
	std::cout << "CMD PING" << std::endl;
#endif
	// if (user.getFd() == user.end())
		// return ;
    if (send(user.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
		perror("Error send msg ping to client");
	}
}

void	Server::pingTime( void ) {
	// tentative ping timeout mais echec !
	double tmp;
	// std::string msg;
	std::map<const int, User>::iterator it = _users.begin(), ite = _users.end();

	for (; it != ite; it++) {
		tmp = difftime(time(NULL), it->second.getTimeActivity());
		if (tmp > PING_TIME && it->second.getPingStatus() == false) {
			cmdPing(it->second, it->second.getHostname());
			// msg = PING(it->second.getHostname());
			// if (send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
			// 	perror("Error send msg ping to client");
			// }
			it->second.setPingStatus(true);
			it->second.setTimeActivity();
		}
		else if (it->second.getPingStatus() == true) {
			// msg.clear();
			// msg = "Erreur ping TimeOut";
			tmp = difftime(time(NULL), it->second.getTimeActivity());
			if (tmp > PING_TIME) {
				cmdPing(it->second, "Erreur ping timeOut\n");
				// if (send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1) {
				// 	perror("Error send msg ping to client");
				// }
				//kill client !
				killUserClient(it->second);
			}
		}
	} 
}