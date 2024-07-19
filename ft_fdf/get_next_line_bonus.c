/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:14:16 by ael-moha          #+#    #+#             */
/*   Updated: 2024/02/18 15:18:06 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_strchr_bool(char *s, int c)
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

char	*ft_getline(char **line)
{
	char	*remain;
	char	*tmp;
	size_t	i;

	i = 0;
	while (line[0][i] != '\n' && line[0][i] != '\0')
		i++;
	if (line[0][i] == 0 || line[0][1] == 0)
		return (NULL);
	remain = ft_substr(*line, i + 1, ft_strlen(*line) - i);
	if (remain == NULL || *remain == 0)
	{
		free(remain);
		return (NULL);
	}
	tmp = *line;
	*line = ft_substr(tmp, 0, i + 1);
	free(tmp);
	line[0][i + 1] = '\0';
	return (remain);
}

char	*ft_readfile(int fd, char *remain, char *buffer)
{
	ssize_t	byteread;
	char	*tmp;

	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread < 0)
			return (NULL);
		if (byteread == 0)
			break ;
		if (!remain)
			remain = ft_strdup("");
		buffer[byteread] = '\0';
		tmp = remain;
		remain = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr_bool(buffer, '\n'))
			break ;
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0
		|| BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = (char *)malloc((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_readfile(fd, remain[fd], buffer);
	free(buffer);
	if (!line)
	{
		free(remain[fd]);
		remain[fd] = NULL;
		return (NULL);
	}
	remain[fd] = ft_getline(&line);
	return (line);
}
