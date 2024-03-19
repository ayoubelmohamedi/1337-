

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
    char        *row;
    int         **table;
    char        *tmp;
    size_t      i;
    size_t      linecount;
    size_t      col;

    if (c != 2)
        return (1);
    filename = argv[1]; 
    linecount = ft_countlines(filename); 

    fd = open(filename,O_RDONLY);
    row = get_next_line(fd);
    col = ft_colcount(row,' '); 
    printf("content of row =%s \n", row);
    printf("rows = %zu\n", linecount);
    printf("cols = %zu\n", col);

    table = malloc(sizeof(int*) * linecount);
    i = 0;

    while(row != NULL)
    {
        tmp  = row;
        table[i] = ft_split_int(row, ' ');
        row = get_next_line(fd);
        printf("%ld => %s\n",i , row);
        i++;
        free((char *)tmp);
    }
    printf("outside from loop\n");
    i = 0;
    int j = 0;
    int count = 0;
    while (j < linecount)
    {
        printf("[");

        while (i < col)
        {
            count++;
            printf("%d, ", table[j][i++]);
        }
        printf("] => len is  %d\n",count);
        i = 0;
        j++;
    }

    printf("times = %d\n", j);
    free(row);
    free(table);
    return (0);
}



   