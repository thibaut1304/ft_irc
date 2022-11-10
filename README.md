# IRC

Client IRC linux : https://www.tecmint.com/best-irc-clients-for-linux/

Liste dependance pour weechat : https://weechat.org/files/doc/stable/weechat_user.en.html#install[WeeChat%20user's%20guide]

Socket : https://www.geeksforgeeks.org/socket-programming-cc/

Select VS poll -> https://devarea.com/linux-io-multiplexing-select-vs-poll-vs-epoll/#.Y0xRjtJBzd4

# A faire

- Verifier les caractere interdit sur toute les commande ! pour nick -> " ,*?!@$:."

- Sur la commande QUIT informer les autres utilisateur si l'user est dans un channel que une personne a quitter le serveur dans le channel


# Actual commands to do

- [x] PASS
- [x] NICK
- [W] TOPIC
- [x] USER
- [W] MODE
- [A] KICK
- [x] PING
- [A] JOIN
- [T] WHO
- [x] PRIVMSG
- [A] PART
- [T] QUIT
- [A] INVITE

# REFERENCE
https://www.rfc-editor.org/rfc/rfc1459

# REGISTER A USER
NICK <nickname> // NO SPECIAL CHARACTERS " ,*!?@$:;" (same as username below)
USER <username> <hostname> <servername> :<realname>
PASS <pass>

# COMMANDS
## Connection Registration
- [ ] PASS
- [x] NICK
- [x] USER
- [ ] SERVER
- [ ] OPER
- [x] QUIT
- [ ] SQUIT

## Channel Operations
- [X] JOIN
- [A] PART
- [A] MODE
	- [A] CHANNEL MODES
	- [A] USER MODES
- [A] TOPIC
- [X] NAMES
- [X] LIST
- [A] INVITES
- [A] KICK

## Server queries and commands
- [ ] VERSION
- [ ] STATS
- [ ] LINKS
- [ ] TIME
- [ ] CONNECT
- [ ] TRACE
- [ ] ADMIN
- [ ] INFO

## Sending messages
- [ ] PRIVMSG
- [ ] NOTICE

## User based queries
- [ ] WHO
- [ ] WHOIS
- [ ] WHOWAS

## Misc messages
- [T] KILL
- [T] PING
- [ ] PONG
- [ ] ERROR

## Optional messages
- [ ] AWAY
- [ ] REHASH
- [ ] RESTART
- [ ] SUMMON
- [ ] USERS
- [ ] WALLOPS
- [ ] USERHOST
- [ ] ISON

