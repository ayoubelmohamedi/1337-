#ifndef FT_FDF_H
# define FT_FDF_H

//to remove
#include <stdio.h>

#include <fcntl.h>
#include <stdlib.h>

#include "mlx.h"
#include "libft/libft.h"


typedef struct  s_point
{
    size_t x;
    size_t y;
    size_t z;
    int color;

} t_point;


size_t      ft_colcount(const char *s, char c);
int         *ft_split_int(const char *str, char c);
size_t      ft_countlines(char *filename);

char	*get_next_line(int fd);
char	*ft_readfile(int fd, char *remain, char *buffer);
char	*ft_getline(char **line);
int		ft_strchr_bool(char *s, int c);

t_point *coordinatesTable(int ** table, size_t col, size_t row);
int ** make_table(char *filename);



#endif