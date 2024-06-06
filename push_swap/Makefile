

CC = cc -g
CFLAGS = -Wall -Wextra -Werror
SRC = ft_helper.c ft_push_ab.c ft_push_swap.c ft_reverse_rotate.c \
		ft_rotate.c ft_split.c ft_helper2.c ft_swap_moves.c \
		ft_helper_parsing.c

OBJ = $(SRC:.c=.o)
NAME = push_swap

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re