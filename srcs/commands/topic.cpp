/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:24:21 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/10 21:01:12 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static void get_topic(Server * server, User user)
{
	int               destination = user.getFd();
	BUFFER_           buffer      = server->_allBuff;
	BUFFER_::iterator it          = buffer.begin();

	if (buffer.size() == 2)
	{
		std::string ch_name  = it[1];
		Channel     *channel = server->getChannel(ch_name);
		std::string topic    = channel->getTopic();
		std::string msg;

		if (channel->isAdmin(user.getNickname()) == false)
		{
			msg += ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getName());
			send(user.getFd(), msg.c_str(), msg.length(), 0);
			return;
		}

		if (topic.size() == 0)
		{
			msg = ch_name + " :No topic is set\r\n";
			send_to_client(destination, msg, "331");
			return ;
		}
		msg = ch_name + " :" + topic + "\r\n";
		send_to_client(destination, msg, "332");
	}
}

static void set_topic(Server * server, User user)
{
	BUFFER_           buffer = server->_allBuff;
	BUFFER_::iterator it     = buffer.begin();
	std::string msg;

	if (buffer.size() == 3)
	{
		std::string ch_name   = it[1];
		std::string new_topic = it[2];
		Channel     *channel   = server->getChannel(ch_name);

		if (channel->isAdmin(user.getNickname()) == false)
		{
			msg += ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getName());
			send(user.getFd(), msg.c_str(), msg.length(), 0);
			return;
		}

		channel->setTopic(new_topic);
		std::string msg = "Topic set : " + new_topic;
		channel->sendToAll(&user, "TOPIC", new_topic);
	}
}

void topic(Server * server, User user)
{
	if (check_ERR_NEEDMOREPARAMS (server, user) == NOT_OK_) return ;
	if (check_ERR_NOTREGISTERED  (server, user) == NOT_OK_) return ;
	if (check_ERR_NOSUCHCHANNEL  (server, user) == NOT_OK_) return ;
	if (check_ERR_NOTONCHANNEL   (server, user) == NOT_OK_) return ;

	get_topic(server, user);
	set_topic(server, user);
}


//  Command: TOPIC
//   Parameters: <channel> [<topic>]
//
//   The TOPIC message is used to change or view the topic of a channel.
//   The topic for channel <channel> is returned if there is no <topic>
//   given.  If the <topic> parameter is present, the topic for that
//   channel will be changed, if the channel modes permit this action.
//
//
//   Examples:
//
//   :Wiz TOPIC #test :New topic     ;User Wiz setting the topic.
//
//   TOPIC #test :another topic      ;set the topic on #test to "another
//                                   topic".
//
//   TOPIC #test                     ; check the topic for #test.
//
//   Numeric Replies:
//
//           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
//           RPL_NOTOPIC                     RPL_TOPIC
//           ERR_CHANOPRIVSNEEDED
//
//       331     RPL_NOTOPIC
//                        "<channel> :No topic is set"
//        332     RPL_TOPIC
//                        "<channel> :<topic>"
//
//                - When sending a TOPIC message to determine the
//                  channel topic, one of two replies is sent.  If
//                  the topic is set, RPL_TOPIC is sent back else
//                  RPL_NOTOPIC.

//        461     ERR_NEEDMOREPARAMS
//                        "<command> :Not enough parameters"
//
//                - Returned by the server by numerous commands to
//                  indicate to the client that it didn't supply enough
//                  parameters.
//
//  482     ERR_CHANOPRIVSNEEDED
//                        "<channel> :You're not channel operator"
//
//                - Any command requiring 'chanop' privileges (such as
//                  MODE messages) must return this error if the client
//                  making the attempt is not a chanop on the specified
//                  channel.

//        442     ERR_NOTONCHANNEL
//                        "<channel> :You're not on that channel"
//
//                - Returned by the server whenever a client tries to
//                  perform a channel effecting command for which the
//                  client isn't a member.
