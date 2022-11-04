# IRC

Client IRC linux : https://www.tecmint.com/best-irc-clients-for-linux/

Liste dependance pour weechat : https://weechat.org/files/doc/stable/weechat_user.en.html#install[WeeChat%20user's%20guide]

Socket : https://www.geeksforgeeks.org/socket-programming-cc/

Select VS poll -> https://devarea.com/linux-io-multiplexing-select-vs-poll-vs-epoll/#.Y0xRjtJBzd4

# A faire

- Parser les commandes recus ! Enregistrer un user correctement !

- Comprendre les modes, les ping/pong

- Connection avec netcat

- :NickName!UserName@ip JOIN servername :efjeji


# REFERENCE
https://www.rfc-editor.org/rfc/rfc1459

# COMMANDS
## Connection Registration
- [ ] PASS
- [x] NICK
- [x] USER
- [ ] SERVER
- [ ] OPER
- [ ] QUIT
- [ ] SQUIT

## Channel Operations
- [A] JOIN
- [A] PART
- [A] MODE
	- [A] CHANNEL MODES
	- [A] USER MODES
- [A] TOPIC
- [A] NAMES
- [A] LIST
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

