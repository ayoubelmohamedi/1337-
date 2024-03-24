
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
    int      x;
    int      y;
    size_t      i;

    x = 0;
    y = 0;
    i = 0;
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
            coordinates[i] = point;
            printf("added point (%zu,%zu,%zu)\n",point.x, point.y,point.z);
            free(point);
            x++;
        }
        x = 0;
        y++;
    }
    return (coordinates);
}

char *parsedcolors(t_point * points, size_t cols,size_t rows)
{
    size_t c;
    size_t j;
    size_t i;

    c = 0;
    j = 0;
    i = 0;
    while (j < rows) 
    {
        printf("(%d,%d,%d) ",points[i].x, points[i].y,points[i].z);
        if (cols == c)
        {
            c = 0;
            printf("\n-----------------\n");
        }
        c++;
        i++;
        j++;
    }
}
//y = rows && x = cols
void    colorize(t_point *points, size_t rows, size_t cols, char * filename)
{
    char *line;
    char *tmp;
    int fd;
    static size_t i;
    size_t y;

    y = 0;
    if (!i)
        i = 0;
    fd = open(filename, O_RDONLY);
    line = get_next_line(fd);
    while (y < rows)
    {
        tmp = line;
        // points[i++].color = getcolor(line);
        colorLine(&points[i], line);
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

// add -1 from end res  
int getorigin(int x, int y, int cols)
{
    x += 1;
    y += 1;
    return (cols * y - (cols - x));
}