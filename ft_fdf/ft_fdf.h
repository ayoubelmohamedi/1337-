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
# define  DEFAULT_COLOR 0xFFFFFF


#define WIDTH 720
#define HIGHT 720
# define ARROW_LEFT 65361 
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364 
# define ARROW_UP 65362
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define ESCAPE 65307 

typedef struct  s_point
{
    double x;
    double y;
    double z;
    int color;
} t_point;

typedef struct s_color
{
    int x;
    int y;
    int color;
} t_color;

typedef struct camera
{
	double x_angle;
	double y_angle;
	double z_angle;
	double zoom;
} t_camera;

typedef	struct s_data
{
	void	*mlx;
	void 	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	width;
	int		height;	
	int		offset;
	size_t	cols;
	size_t	rows;
	size_t	shift;
	t_camera *camera;
	t_point	**map;
}	t_data;

void 	ft_upper_str(char * text);
t_point	*ft_parseLine(char **splitted, int curr_row, size_t cols);
t_point **ft_genMap(char *filename, size_t rows, size_t cols);
t_point		ft_project (t_point p, t_data * data);
size_t      ft_colcount(const char *s, char c);
int         *ft_split_int(const char *str, size_t cols);
size_t      ft_countlines(char *filename);

char	*get_next_line(int fd);
char	*ft_readfile(int fd, char *remain, char *buffer);
char	*ft_getline(char **line);
int		ft_strchr_bool(char *s, int c);

t_point *coordinatesTable(int ** table, size_t col, size_t row);
int     **make_table(char *filename,size_t *rows, size_t *cols);


//mapirize 
void	ft_display(t_data *data);
void	mappirize(t_data *data);
void draw_line(t_data * data,t_point p1, t_point p2, int color);

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

void freeMap(t_data * data);
void printTable(t_point **table, size_t rows, size_t cols);
void print_row(t_point **table, size_t rows, size_t cols);
void freeTable(int **table, char * filename);
char *parsedcolors(t_point * points, size_t cols,size_t rows);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
//comment
#endif