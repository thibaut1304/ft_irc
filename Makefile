# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 09:48:37 by thhusser          #+#    #+#              #
#    Updated: 2022/10/17 10:03:49 by thhusser         ###   ########.fr        #
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

FLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3

DIR_INC		= -I ./includes/

SRCS		:= 	main.cpp \
				Server.cpp

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
				@echo "$(_GREEN)Generating $(NAME) $(_NC)"


# $(CLIENT):		$(OBJS_CLIENT)
# 				@$(CC) $(FLAGS) ${DIR_INC} $(OBJS_CLIENT) -o $(CLIENT)
# 				@echo "$(_GREEN)Generating $(CLIENT) $(_NC)"
clean:
		@$(RM) $(DIR_OBJ)
		@echo "$(_GREEN)Deletes objects files $(NAME) $(_NC)"

fclean:		clean
			@$(RM) $(NAME) $(CLIENT)
			@echo "$(_GREEN)Delete $(NAME) $(_NC)"

re:			fclean all
