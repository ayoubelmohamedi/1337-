/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:42:51 by ael-moha          #+#    #+#             */
/*   Updated: 2024/02/14 13:18:34 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if (s[i] == (char)c)
		return (1);
	return (0);
}


char	*ft_joinfree(char **remain, char **buffer, ssize_t byteread)
{
	char	*res;

	if (byteread < 0 || (byteread == 0 && ft_strlen(*remain) == 0))
	{
		free(*remain);
		free(buffer);
		*remain = NULL;
		return (NULL);
	}
	buffer[byteread] = 0;
	res = ft_strjoin(*buffer, *remain);
	free(*buffer);
	return (res);
}

char	*ft_getline(char **remain)
{
	char	*line;
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	while (remain[0][i] != '\0' && remain[0][i] != '\n')
		i++;
	tmp = *remain;
	line = ft_substr(tmp, 0, i + 1);
	j = i + 1;
	while (remain[0][i] != '\0')
		i++;
	*remain = ft_substr(tmp, j, i);
	free(tmp);
	if (!line || !*remain)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remain;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = (char *)ft_readfile(fd, &remain);
	if (!remain)
		return (NULL);
	if (ft_strlen(remain) == 0)
	{
		free(remain);
		remain = NULL;
		return (0);
	}
	return (ft_getline(&remain));
}

char	*ft_readfile(int fd, char **res)
{
	char	*buffer;
	ssize_t	byteread;

	buffer = (char *)malloc((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!*res)
		*res = ft_strdup("");
	byteread = read(fd, buffer, BUFFER_SIZE);
	while (byteread > 0)
	{
		*res = ft_joinfree(&buffer, res, byteread);
		if (!*res)
			return (NULL);
		if (ft_strchr(*res, '\n') || byteread == 0)
		{
			free(buffer);
			break ;
		}
		byteread = read(fd, buffer, BUFFER_SIZE);
	}
	if (byteread == 0)
		free(buffer);
	return (*res);
}



//#include <stdio.h>
//
// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char * line = get_next_line(fd);
// 	// char * line2 = get_next_line(fd);
// 	// char * line3 = get_next_line(fd);
// 	// char * line4 = get_next_line(fd);
// 	// char * line5 = get_next_line(fd);
//
// 	printf("%s",line);
// 	// printf("%s",line2);
// 	// printf("%s",line3);
// 	// printf("%s",line4);
// 	// printf("%s",line5);
//
// 	free(line);
// 	// free(line2);
// 	// free(line3);
// 	// free(line4);
// 	// free(line5);
//
// 	return (0);
// }
