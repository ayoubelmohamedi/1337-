




#include => $(NAME), all, clean, fclean and re

NAME = fdf
## to add -Wall -Wextra -Werror  
CFLAGS = -g -O3 
SRCS = mlxtest.c
OBJS = ${SRCS:.c=.o}
RM 	 = rm -rf

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)

re:
	fclean all