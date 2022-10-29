# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 09:48:37 by thhusser          #+#    #+#              #
#    Updated: 2022/10/29 17:33:03 by thhusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

DEBUG = 1

OS		=		$(shell echo -n ${GDMSESSION})

NAME		=		ft_irc

CLIENT		=		client

RM	=	rm -rf

CC	=	c++

FLAGS	=	-Wall -Wextra -Werror -std=c++98 -g

DIR_INC		= -I ./includes/

SRCS		:= 	main.cpp \
				Server.cpp \
				User.cpp \
				commands/ping.cpp \
				# parsing.cpp

SRCS_CLIENT := client.cpp \
				

DIR_SRCS	:= ./srcs

DIR_OBJ	:= obj

OBJS	:= \
			$(addprefix ${DIR_OBJ}/, ${SRCS:.cpp=.o})

# OBJS_CLIENT	:= \
			# $(addprefix ${DIR_OBJ}/, ${SRCS_CLIENT:.cpp=.o})
			
DEPS = $(OBJS:.o=.d)
			
all: $(NAME)
# $(CLIENT)

-include $(DEPS)

$(DIR_OBJ)/%.o:	$(DIR_SRCS)/%.cpp
		@mkdir -p $(dir $@)
		@${CC} ${FLAGS} ${DIR_INC} -o $@ -c $< -MMD

$(NAME):			$(OBJS)
				 @$(CC) $(FLAGS) ${DIR_INC} $(OBJS) -o $(NAME)
				@printf "$(_GREEN)Generating $(NAME) $(_NC)\n"

clean:
		@$(RM) $(DIR_OBJ)
		@printf "$(_GREEN)Deletes objects files $(NAME) $(_NC)\n"

fclean:		clean
			@$(RM) $(NAME) $(CLIENT)
			@printf "$(_GREEN)Delete $(NAME) $(_NC)\n"

re:			fclean all
