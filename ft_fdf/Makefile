# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 17:41:53 by ael-moha          #+#    #+#              #
#    Updated: 2024/08/21 23:25:28 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCS = ft_fdf.c get_next_line_bonus.c ft_helper.c ft_helper2.c \
		ft_parser.c  ft_rotation.c ft_error_handle.c ft_error_helper.c

OBJS = ${SRCS:.c=.o}
RM 	 = rm -rf
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all