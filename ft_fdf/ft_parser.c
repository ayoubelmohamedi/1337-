
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

t_point ** fill_cortable(int ** table, size_t col, size_t row)
{
    t_point     *coordinates;
    t_point     point;
    size_t      x;
    size_t      y;

    x = 0;
    y = 0;
    while (y < row)
    {
        while (x < col)
        {
            point.x = x;
            point.y = y;
            point.z = table[x][y];

            printf("added point (%zu,%zu,%zu)\n",point.x, point.y,point.z);
            x++;
        }
        y++;
    }
}