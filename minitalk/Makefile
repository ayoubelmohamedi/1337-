# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 06:33:00 by ael-moha          #+#    #+#              #
#    Updated: 2024/04/22 06:33:04 by ael-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		= ./libft/libft.a
CC			= cc
CFLAGS   	= -Wall -Wextra -Werror
RM			= rm -rf

SERVER  = server
CLIENT	= client

CLIENT_BONUS = client_bonus
SV_BONUS	= server_bonus

CLIENT_SRS = client.c
SV_SRS = server.c

CL_BONUS_SRS = client_bonus.c
SV_BONUS_SRS = server_bonus.c


all:	$(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C ./libft

$(SERVER): $(LIBFT) $(SV_SRS)
	$(CC) $(CFLAGS) $(SV_SRS) $(LIBFT) -o server

$(CLIENT): $(LIBFT) $(CLIENT_SRS)
	$(CC) $(CFLAGS) $(CLIENT_SRS) $(LIBFT) -o client	

$(CLIENT_BONUS): $(LIBFT) $(CL_BONUS_SRS)
	$(CC) $(CFLAGS) $(CL_BONUS_SRS) $(LIBFT) -o client_bonus

$(SV_BONUS): $(LIBFT) $(SV_BONUS_SRS)
	$(CC) $(CFLAGS) $(SV_BONUS_SRS) $(LIBFT) -o server_bonus

bonus : $(SV_BONUS) $(CLIENT_BONUS)

clean:
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	${RM} ${SERVER} ${CLIENT}
	${RM} ${SV_BONUS} ${CLIENT_BONUS}

re: fclean all

