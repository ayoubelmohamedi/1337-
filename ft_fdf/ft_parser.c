
#include "ft_fdf.h"



int *ft_split_int(const char *str, char c)
{
    int     *res;
    char    ** nbrsting;
    size_t  col;
    size_t  i;

    col = ft_colcount(str, c);
    nbrsting = ft_split(str, c);
    res = malloc(sizeof(int) * col);
    if (!res)
        return (NULL);
    i = 0;
    while (i < col)
    {
        res[i] = ft_atoi(nbrsting[i]);
        i++;
    }
    i = 0;
    while (i < col)
        free(nbrsting[i++]);
    free(nbrsting);
    return (res);
}

int ** make_table(char *filename,size_t *rows, size_t *cols)
{
    char    *row;
    char    *tmp;
    int    **table;
    size_t  linecount;
    size_t i;
    int fd;

    i = 0;
    linecount = ft_countlines(filename); 
    *rows = linecount;
    table = malloc(sizeof(int*) * linecount);
    if (!table)
        return (NULL);
    fd = open(filename, O_RDONLY);
    row = get_next_line(fd);
    *cols = ft_colcount(row, ' ');
    while (row != NULL)
    {
        tmp  = row;
        table[i++] = ft_split_int(row, ' ');
        row = get_next_line(fd);
        free((char *)tmp);
    }
    free(row);
    close(fd);
    return (table);
}
t_point * coordinatesTable(int ** table, size_t col, size_t row)
{
    t_point     *coordinates;
    t_point     point;
    size_t      x;
    size_t      y;

    x = 0;
    y = 0;
    coordinates = (t_point *)malloc(sizeof(point) * (col * row));
    if (!coordinates)
        return (NULL);
    while (y < row)
    {
        while (x < col)
        {
            printf("x = %zu, y = %zu\n", x,y);
            point.x = x;
            point.y = y;
            point.z = table[x][y];
            point.color = 0;
            printf("added point (%zu,%zu,%zu)\n",point.x, point.y,point.z);
            x++;
        }
        x = 0;
        y++;
    }
    return (coordinates);
}
//y = rows && x = cols
void    colorize(t_point *points, size_t rows, size_t cols, char * filename)
{
    char *line;
    char *tmp;
    int fd;
    size_t i;
    size_t y;

    y = 0;
    fd = open(filename, O_RDONLY);
    line = get_next_line(fd);
    while (y < rows)
    {
        tmp = line;
        // points[i++].color = getcolor(line);
        colorLine(points, line);
        line = get_next_line(fd);
        free(tmp);
        y++;
    }
    close(fd);
}

void    colorLine(t_point *points,char *line)
{
    int hex;
    size_t i;
    size_t x;

    i = 0;
    x = 0;
    printf("line =>%s\n",line);
    while ((line[i] != '\n' || line[i] != '\0') && line[i])
    {
        if (line[i] == ',')
        {
            i++;
            points[x++].color = convert_hex(gethex(&line[i],&i));
        }
        i++;
    }
}