
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
    while (nbrsting[i])
        res[i++] = ft_atoi(nbrsting[i]);
    i = 0;
    while (nbrsting[i])
        free(nbrsting[i++]);
    free(nbrsting);
    return (res);
}

int ** make_table(char *filename,size_t *rows, size_t *cols)
{
    int **table;
    char *line;
    int fd;
    size_t i;

    fd = open(filename, O_RDONLY);
    if (fd < -1)
        return (NULL);
    line = get_next_line(fd);
    *cols = ft_colcount(line, ' ');
    *rows = ft_countlines(filename);
    i = 0;
    printf("table has allocated %zu bytes\n",(*rows) * (*cols));
    table = malloc(sizeof(int*) * ((*rows) * (*cols)));
    if (!table)
    {
        free(line);
        return (NULL);
    }
    while (line) 
    {
        printf("i is now %zu\n",i);
        table[i++] = ft_split_int(line,' ');
        free(line);
        line  = get_next_line(fd);
    }
    free(line);
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
            point.x = y;
            point.y = x;
            point.z = table[y][x];

            point.color = 0;
            coordinates[i++] = point;
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

int hascolor(char *filename)
{
    int c;
    int i;
    int fd;
    char *row;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    row = get_next_line(fd);
    c = 0;
    while (row)
    {
        i = 0;
        while (row[i++])
            if (row[i] == ',')
                c++;
        row = get_next_line(fd);
    }
    free(row);
    close(fd);
    return (c);
}

t_color *cor_colors(char *filename)
{
    t_color *colors;
    size_t i;
    int nbrColors;

    nbrColors = hascolor(filename); 
    if (!nbrColors || nbrColors == -1)
        return (NULL);
    colors = (t_color*) malloc(sizeof(t_color*) * nbrColors);
    // while () 
     
    return (colors);
}

// //y = rows && x = cols
// void    colorize(t_point *points,t_color * colors, size_t rows, size_t cols, char * filename)
// {
//     char *line;
//     char *tmp;
//     int fd;
//     static size_t i;
//     size_t y;

//     y = 0;
//     if (!i)
//         i = 0;
//     fd = open(filename, O_RDONLY);
//     line = get_next_line(fd);
//     while (y < rows)
//     {
//         tmp = line;
//         // points[i++].color = getcolor(line);
//         colorLine(&points[i], line);
//         line = get_next_line(fd);
//         free(tmp);
//         y++;
//     }
//     close(fd);
// }

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