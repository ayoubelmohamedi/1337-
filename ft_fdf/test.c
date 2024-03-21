

#include<stdio.h>
#include "libft/libft.h"
#include "ft_fdf.h"


size_t	ft_strcount(char *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s != NULL && *s != '\0')
	{
		if (*s != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (count);
}

int *ft_split_int(char *str, char c)
{
    int     *res;
    char    ** nbrsting;
    size_t  col;
    size_t  i;

    col = ft_strcount(str, c);
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

int main()
{
    t_point *points;

    t_point point1;
    t_point point2;
    t_point point3;
    t_point point4;
    t_point point5;
    t_point point6;

    point1 = {0,0,27,0};
    point2 = {0,1,20,0};
    point3 = {0,2,15,0};
    point4 = {0,3,12,0};
    point5 = {0,4,13,0};
    point6 = {0,5,14,0};

    points[0] = &point1;
    points[1] = &point2;
    points[2] = &point3;
    points[3] = &point4;
    points[4] = &point5;
    points[5] = &point6;



    int arr [] = {11,12,13,9,166};
    int table[4][3]= {{1,2,3} ,{4,5,6}, {7,8,9},{10,11,12}};
    char * line = "27,0x810202 20,0x810202 15,0x810202 12,0x810202 13,0x810202 12,0x810202";
    colorLine(points,line)

    return (0);
}