/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:51:42 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/21 23:51:43 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BASE16 "0123456789ABCDEF"
# define DEFAULT_COLOR 0xFFFFFF

# define WIDTH 720
# define HEIGHT 720
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

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_point;

typedef struct camera
{
	double		x_angle;
	double		y_angle;
	double		z_angle;
	double		zoom;
}				t_camera;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			offset;
	size_t		cols;
	size_t		rows;
	size_t		shift;
	t_camera	*camera;
	t_point		**map;
}				t_data;

// error handling
void			ft_error(char *filename, int error);
int				is_valid(char *filename);
size_t			ft_getcols_line(char *line);

// error helpers
size_t			ft_count_elements(char **str);
void			free_split(char **str);
size_t			count_cols(char *line);

void			init_camera(t_data *data);
double			ft_min(double a, double b);
void			ft_upper_str(char *text);
t_point			*ft_parse_line(char **splitted, int curr_row, size_t cols);
t_point			**ft_gen_map(char *filename, size_t rows, size_t cols);
t_point			ft_project(t_point p, t_data *data);
size_t			ft_colcount(const char *s, char c);
int				*ft_split_int(const char *str, size_t cols);
size_t			ft_countlines(char *filename);

char			*get_next_line(int fd);
char			*ft_readfile(int fd, char *remain, char *buffer);
char			*ft_getline(char **line);
int				ft_strchr_bool(char *s, int c);

t_point			*coordinatesTable(int **table, size_t col, size_t row);
int				**make_table(char *filename, size_t *rows, size_t *cols);
int				ft_destroy(t_data *data);

// mapirize
void			ft_display(t_data *data);
void			mappirize(t_data *data);
void			draw_line(t_data *data, t_point p1, t_point p2);

// utils
size_t			ft_getcols(char *filename);
size_t			ft_getrows(char *filename);
void			free_map(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif