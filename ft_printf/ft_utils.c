#include "ft_printf.h"

int	ft_strchr(char c)
{
	char	*str;

	str = "diuxXcsp";
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

int	ft_allspaces(const char *str)
{
	int	allspace;

	allspace = 1;
	while (*str != '\0')
	{
		if (*str != ' ')
			allspace = 0;
		str++;
	}
	return (allspace);
}

int	ft_shorten(const char **str)
{
	int i;

	i = 0;
	if ((*str)[i] == ' ')
		write(1, (*str), 1);
	while ((*str)[i] == ' ' && (*str)[i] != '\0')
		i++;
	(*str) += (i--);
	if (i > 0)
		return (1);
	return (0);
}