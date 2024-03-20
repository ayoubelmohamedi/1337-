

#include<stdio.h>
#include "libft/libft.h"

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
    
    int arr [] = {11,12,13,9,166};
    int table[4][3]= {{1,2,3} ,{4,5,6}, {7,8,9},{10,11,12}};


    size_t cols = sizeof(table[0]) / sizeof(table[0][0]);
    size_t rows = sizeof(table) / sizeof(table[0]); 

    printf("cols => %zu\n", cols);
    printf("rows => %zu\n", rows);
    return (0);
}