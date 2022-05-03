# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 16:03:42 by elpastor          #+#    #+#              #
#    Updated: 2022/04/28 16:25:33 by elpastor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

DIR_S = srcs/

HEADER = includes/

SOURCES = pipex.c \
		utils.c \
		get.c

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = ${SRCS:.c=.o}

FLAGS = -I $(HEADER) -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	cc ${FLAGS} -c $^ -o $@

${NAME}: ${OBJS} $(HEADER)
	cc ${FLAGS} ${OBJS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

.PHONY: all clean fclean re
