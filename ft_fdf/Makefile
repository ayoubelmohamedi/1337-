# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 17:41:53 by ael-moha          #+#    #+#              #
#    Updated: 2024/05/06 21:39:47 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include => $(NAME), all, clean, fclean and re

NAME = fdf
## to add -Wall -Wextra -Werror  
CC = cc
CFLAGS = -O3 -g #-fsanitize=address
SRCS = mlxtest.c get_next_line_bonus.c ft_helper.c

OBJS = ${SRCS:.c=.o}
RM 	 = rm -rf
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft
MLX_DIR = ./mlx
MLX_LIB =  $(MLX_DIR)/libmlx_Darwin.a
MLXFLAGS =  -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
X11_FLAGS = -L/usr/X11/lib -lXext -lX11

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
# $(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
# 	$(CC) $(OBJS) $(LIBFT) $(MLXFLAGS) $(X11_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all