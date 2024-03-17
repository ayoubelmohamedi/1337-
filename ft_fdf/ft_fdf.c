

//isometric projection
// destination.x = source.x + cos(angle) * source.z
// destination.y = source.y + sin(angle) * source.z

// typedef struct fdf
// {
//     /* data */
// };


// void draw_table(table)
// {
//     int pixelx;
//     int pixely;

// }
#include "ft_fdf.h"


size_t ft_countlines(char *filename)
{
    size_t c;
    int fd; 
    char *line;
    char * tmp;

    c = 0;
    fd = open(filename, O_RDONLY);
    line = get_next_line(fd);
    while (line != NULL)
    {
        c++;
        tmp = line;
        line = get_next_line(fd);
        free(tmp);
    }
    if (line)
        free(line);
    close(fd);
    return (c);
}

int main (int c, char * argv[])
{
    char        *filename;
    int         fd;
    const char  *row;
    int         **table;
    const char  *tmp;
    size_t      i;
    size_t linecount;

    if (c != 2)
        return (1);

    filename = argv[1]; 
    linecount = ft_countlines(filename); 
    printf("lines count => %zu\n", linecount);

    fd = open(filename,O_RDONLY);
    row = get_next_line(fd);
    table = malloc(sizeof(int*) * linecount);
    i = 0;
    while(row != NULL)
    {
        tmp  = row;
        table[i++] = ft_split_int(row, ' ');
        row = get_next_line(fd);
        free((char *)tmp);
    }
    close(fd);
    return (0);
}