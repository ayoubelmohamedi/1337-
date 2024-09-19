# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 17:11:24 by ael-moha          #+#    #+#              #
#    Updated: 2024/08/27 17:52:41 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -I../libft/
NAME = philo 
CC = cc
# CFLAGS   =	-Wall -Wextra -Werror 
CFLAGS = -g 
SRCS = ft_philo.c ft_helpers.c ft_errors.c
OBJS = $(SRCS:.c=.o)

RM = rm -f
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@ 

$(NAME): $(OBJS) 
	$(CC) $(OBJS)  -o $(NAME) 

clean:
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re : fclean all