

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
    const char *str =  malloc(4 * sizeof(char));
    int i = 0;
    while (i < 4) 
    {
        str[i] = 'A';
        i++;
    }

    free(res);
    return (0);
}