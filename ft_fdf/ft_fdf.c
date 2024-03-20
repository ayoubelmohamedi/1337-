

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
    char *line;
    char *tmp;
    int fd;

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
    close(fd);
    if (line)
        free(line);
    return (c);
}


int main (int c, char * argv[])
{
    int         fd;
    char        *row;
    int         **table;
    char        *filename;

    if (c != 2)
        return (1);

    filename = argv[1];
    fd = open(filename,O_RDONLY);
    table = make_table(filename);

    printf("filename => %s\n", argv[1]);

    int i = 0;
    int j = 0;
    size_t col = ft_countlines(filename);
    row = get_next_line(fd);
    printf("col = %zu\n", col);
    printf("getnextline = %s\n", row);
    char *tmp;
    while (row != NULL)
    {
        printf("inside\n");
        tmp = row;
        while (j < col)
            printf("%d, ",table[i][j++]);
        printf("\n");
        i++;
        row = get_next_line(fd);
        free(row);
    }
    printf("]\n");
    if (!table)
    {
        close(fd);
        return (0);
    }
    free(row);
    free(table);
    return (0);
}



   