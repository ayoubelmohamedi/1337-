# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 13:55:16 by ael-moha          #+#    #+#              #
#    Updated: 2023/12/22 13:55:20 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS =  ft_handle_hex.c  ft_handleptr.c	ft_handle_usign.c \
		ft_handle_nbr.c ft_handle_str.c ft_printf.c ft_utils.c \


NAME	= libftprintf.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror 
RM		= rm -f

OBJS = ${SRCS:.c=.o}

all: $(NAME)

${NAME}: ${OBJS} 

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@ 
	ar	rcs	${NAME} $@

clean:
	${RM} ${OBJS}
fclean: clean
	${RM} ${NAME}

re:	fclean all

