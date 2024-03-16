

LIB = libgetnextline.a

SRC_FILES =  get_next_line.c get_next_line_utils.c 

BNJ_FILES = get_next_line_utils_bonus.c get_next_line_bonus.c

HDR_FILES = get_next_line.h
HDR_BONUS =	get_next_line_bonus.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

OBJS = ${SRC_FILES:.c=.o}
OBJS_BNS = ${BNJ_FILES:.c=.o}
OBJ_FILES = ${OBJS_BNS} ${OBJS}

all: ${LIB}

${LIB}: ${OBJS} ${OBJS_BNS}

%.o : %.c ${HDR_FILES} ${HDR_BONUS}
	${CC} ${CFLAGS} -c $< -o $@
	ar rcs ${LIB} $@ 


clean:
	${RM} ${OBJ_FILES} 

fclean: clean
	${RM} ${LIB}
re: fclean all

.PHONY: all clean