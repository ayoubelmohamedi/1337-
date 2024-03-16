#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
#include <fcntl.h>

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

int main (int c, char * argv[])
{
    char    *filename;
    int     fd;
    if (c != 2)
        return (1);

    filename = argv[1];
    fd = open(filename,O_RDONLY);
    

    return (0);
}