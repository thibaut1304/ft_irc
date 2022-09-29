# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 09:48:37 by thhusser          #+#    #+#              #
#    Updated: 2022/09/29 12:38:21 by thhusser         ###   ########.fr        #
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

TEST = 1

OS		=		$(shell echo -n ${GDMSESSION})

NAME		=		ft_irc

RM	=	rm -rf

CC	=	c++

FLAGS	=	-Wall -Wextra -Werror -std=c++98

DIR_INC		= -I ./includes/

SRCS		:= 	main.cpp \
				

DIR_SRCS	:= ./srcs/

DIR_OBJ	:= obj
OBJS	:= \
			$(addprefix ${DIR_OBJ}/, ${SRCS:.cpp=.o})


all: $(NAME)


$(DIR_OBJ)/%.o:	$(DIR_SRCS)/%.cpp
		@mkdir -p $(dir $@)
		@${CC} ${FLAGS} ${DIR_INC} -DTEST=$(TEST) -o $@ -c $<

$(NAME):			$(OBJS)
				 @$(CC) $(FLAGS) ${DIR_INC} $(OBJS) -o $(NAME)
				@echo "$(_GREEN)Generating $(NAME) $(_NC)"

clean:
		@$(RM) $(DIR_OBJ)
		@echo "$(_GREEN)Deletes objects files $(NAME) $(_NC)"

fclean:		clean
			@$(RM) $(NAME)
			@echo "$(_GREEN)Delete $(NAME) $(_NC)"

re:			fclean all
