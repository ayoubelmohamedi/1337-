

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


// int main (int c, char * argv[])
// {
//     int         fd;
//     char        *row;
//     int         **table;
//     char        *filename;
//     t_point     *points; 
//     size_t      rows;
//     size_t      cols;

//     if (c != 2)
//         return (1);

//     filename = argv[1];
//     fd = open(filename,O_RDONLY);
//     table = make_table(filename, &rows, &cols);

//     printf("rows %zu, cols %zu \n",rows, cols);
//     // printTable(table, rows, cols);

//     printf("number of rows => %zu\n", rows);
//     printf("number of cols => %zu\n", cols);
//     // printTable(table, rows, cols);
//     points = coordinatesTable(table, cols, rows);

//     int i = 0;
//     int count = 0;
//     while (i < (cols * rows))
//     {
//         printf("point(%d, %d, %d) ",points[i].x,points[i].y,points[i].z);
//         i++;
//     }
//     // colorize(points, rows, cols, filename);
//     // parsedcolors(points,cols,rows);

//     close(fd);
//     return (0);
// }

void printTable(t_point **table, size_t rows, size_t cols)
{
    size_t i;
    size_t r;

    i = 0;
    r = 0;
    while (r < rows)
    {
        // printf("%d  | ",table[r][i]);
        while (i < cols)
        {
            printf("%d ", table[r][i].z);
            i++;
        }
        printf("\n");
        i = 0;
        r++;
    }
}

void print_row(t_point **table, size_t rows, size_t cols)
{
    for (int i = 0; i < 7; i++)
        printf("%d ", table[9][i].z);
    printf("\n");
}

// void freeTable(int **table, char * filename)
// {
//     char *row;
//     char *tmp;
//     int fd;
//     size_t cols;
//     size_t i = 0;
//     size_t j = 0;

//     fd = open(filename, O_RDONLY);
//     row = get_next_line(fd);
//     cols = ft_colcount(row, ' ');
//     while (row)
//     {
//         tmp = row;
//         while (j < cols)
//             free(&table[i][j++]);
//         j = 0;
//         free(&table[i++]);
//         printf("\n");
//         row = get_next_line(fd);
//         free(tmp);
//     }
//     free(row);
//     close(fd);
// }
   