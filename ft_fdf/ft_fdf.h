#ifndef FT_FDF_H
# define FT_FDF_H

//to remove
#include <stdio.h>

#include <fcntl.h>
#include <stdlib.h>
#include <math.h> 

#include "mlx.h"
#include "libft/libft.h"

# define BASE16 "0123456789ABCDEF"

typedef struct  s_point
{
    size_t x;
    size_t y;
    size_t z;
    unsigned int color;
} t_point;

size_t      ft_colcount(const char *s, char c);
int         *ft_split_int(const char *str, char c);
size_t      ft_countlines(char *filename);

char	*get_next_line(int fd);
char	*ft_readfile(int fd, char *remain, char *buffer);
char	*ft_getline(char **line);
int		ft_strchr_bool(char *s, int c);

t_point *coordinatesTable(int ** table, size_t col, size_t row);
int ** make_table(char *filename,size_t *rows, size_t *cols);

//colorize
void    colorize(t_point *points, size_t rows, size_t cols, char * filename);
void    colorLine(t_point *points,char *line);

//utils
unsigned int convert_hex(char *hex);
char        *reverse(char *str);
int         get_hexpos(char *hex, char c);



//to delete 
void printTable(int **table, char *filename);
void freeTable(int **table, char * filename);

#endif