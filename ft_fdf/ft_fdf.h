#ifndef FT_FDF_H
# define FT_FDF_H

//to remove
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <stdlib.h>
#include <math.h> 

#include "mlx.h"
#include "libft/libft.h"

# define BASE16 "0123456789ABCDEF"

typedef struct  s_point
{
    int x;
    int y;
    int z;
    int color;
} t_point;

typedef struct s_color
{
    int x;
    int y;
    int color;
} t_color;

size_t      ft_colcount(const char *s, char c);
int         *ft_split_int(const char *str, size_t cols);
size_t      ft_countlines(char *filename);

char	*get_next_line(int fd);
char	*ft_readfile(int fd, char *remain, char *buffer);
char	*ft_getline(char **line);
int		ft_strchr_bool(char *s, int c);

t_point *coordinatesTable(int ** table, size_t col, size_t row);
int     **make_table(char *filename,size_t *rows, size_t *cols);

//colorize
// void    colorize(t_point *points,t_color * colors, size_t rows, size_t cols, char * filename)
void    colorLine(t_point *points,char *line);
int getorigin(int x, int y, int cols);
int hascolor(char *filename);
char *getcolor(const char *line, int *i);


//utils
size_t ft_getcols(char *filename);
size_t ft_getrows(char *filename);

// int		ft_fetchColor(char *text);

//to delete 
void printTable(t_point **table, size_t rows, size_t cols);
void print_row(t_point **table, size_t rows, size_t cols);
void freeTable(int **table, char * filename);
char *parsedcolors(t_point * points, size_t cols,size_t rows);



#endif