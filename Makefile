# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 09:48:37 by thhusser          #+#    #+#              #
#    Updated: 2022/11/01 15:01:47 by thhusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_NC     = `tput sgr0`
_RED    = \033[0;31m
_GREEN  = \033[0;32m
_YELLOW = \033[0;33m
_BLUE   = \033[0;34m
_PURPLE = \033[0;95m
_CYAN   = \033[0;36m
_WHITE  = \033[0;37m

DEBUG   = 1
OS      = $(shell echo -n ${GDMSESSION})
NAME    = ft_irc
CLIENT  = client
RM      = rm      -rf
CC      = c++
FLAGS   = -Wall -Wextra -Werror -std=c++98 -g
DIR_INC = -I ./includes/
DIR_INC += -I ./includes/numericReplies/

SRCS		:= 	main.cpp \
				Server.cpp \
				User.cpp \
				commands/ping.cpp \
				commands/connection.cpp \
				commands/nick.cpp \
				commands/kill.cpp \
				utils/print_input_allBuff.cpp \
				utils/server_init.cpp \
				utils/server_launch.cpp \
				utils/server_new_connection.cpp \
				utils/basic_utils.cpp \
				utils/debug.cpp \

# SRCS		+= SRCS_CMD
SRCS_CLIENT := client.cpp
DIR_SRCS    := ./srcs
DIR_OBJ     := obj
OBJS        := $(addprefix ${DIR_OBJ}/, ${SRCS:.cpp=.o})
DEPS        =  $(OBJS:.o=.d)
# OBJS_CLIENT	:= $(addprefix ${DIR_OBJ}/, ${SRCS_CLIENT:.cpp=.o})

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

