# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 17:11:24 by ael-moha          #+#    #+#              #
#    Updated: 2024/09/19 10:02:20 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo 
CC = cc
# CFLAGS   =	-Wall -Wextra -Werror 
CFLAGS = -g -fsanitize=thread
SRCS = ft_philo.c ft_utils.c ft_errors.c ft_routines.c 
OBJS = $(SRCS:.c=.o)

RM = rm -f
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re : fclean all