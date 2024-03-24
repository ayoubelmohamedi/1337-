#include<stdio.h>
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


int main()
{

    printf("inside \n");

    t_point *points;

    points = malloc(sizeof(t_point *) * 6);

    t_point point1= {0,0,27,0};
    t_point point2= {0,1,20,0};
    t_point point3= {0,2,15,0};
    t_point point4= {0,3,12,0};
    t_point point5= {0,4,13,0};
    t_point point6= {0,5,14,0};

    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    points[3] = point4;
    points[4] = point5;
    points[5] = point6;

    printf("z of point6 is %zu\n", points->z);

    int arr [] = {11,12,13,9,166};
    int table[4][3]= {{1,2,3} ,{4,5,6}, {7,8,9},{10,11,12}};
    char * line = "27,0x210202 20,0x30202 15,0x410202 12,0x510202 13,0x610202 12,0x710202";

    int x = 1;
    int y = 1;
    int cols = 3;
    int rows = 3;
    printf("index of (%d, %d) => %d\n",x,y,getorigin(x,y,cols));

    // //TODO:fix indexing 
    // colorLine(points, line);

    // printf("---------------------\n");
    // int i = 0;
    // while (i < 6)
    // {
    //     printf("color of point[%d] => %d\n",i, points[i].color);
    //     i++;
    // }
    // printf("size of hex %u\n",);
    return (0);
}