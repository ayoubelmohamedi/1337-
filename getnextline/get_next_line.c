/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:42:51 by ael-moha          #+#    #+#             */
/*   Updated: 2024/02/16 19:38:19by ael-moha         ###   ########.fr       */
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

// #include <stdio.h>

char	*ft_getline(char **line)
{
	char *remain;
	char *tmp;
	size_t i;
	
	i = 0;
	// printf("ft_getline: *remain => %s\n",*remain);
	//?? wtf is the diff btwen [0] and * ?!
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
	*line = ft_substr(tmp,0, i + 1);
	free(tmp);
	line[0][i + 1] = '\0';
	return (remain);
}

char	*ft_readfile(int fd, char *remain, char *buffer)
{
	ssize_t		byteread;
	char		*tmp;
	
	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread < 0)
			return (NULL);
		if (byteread == 0)
			break;	
		if (!remain)
			remain = ft_strdup("");
		buffer[byteread] = '\0';
		tmp = remain;
		remain = ft_strjoin(tmp,buffer);
		free(tmp);
		if (ft_strchr(buffer,'\n'))
			break;
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char 		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE <= 0 ||BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = (char *)malloc ((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_readfile(fd, remain, buffer);
	free(buffer);
	if (!line)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	remain = ft_getline(&line);
	return (line);
}
// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	printf("fd = %d\n",fd);
// 	// char * line = get_next_line(fd);
// 	// char * line2 = get_next_line(fd);
// 	// char * line3 = get_next_line(fd);
// 	// char * line4 = get_next_line(fd);
// 	// char * line4 = get_next_line(fd);
// 	// char * line5 = get_next_line(fd);


// 	printf("---------------------\n");
// 	// // printf("%s",line);
// 	// // printf("%s",line2);
// 	// // printf("%s",line3);
// 	// // // printf("%s",line4);
// 	// // //printf("%s",line4);
// 	// // //printf("%s",line5);

// 	// free(line);
// 	// free(line2);
// 	// free(line3);

// 	// free(line4);
// 	//free(line5);

// 	//// char * str = ft_strdup("hello\nthere\nlast");
// 	// char * line = ft_getline(&str);
// 	// char * line2 = ft_getline(&str);
// 	// char * line3 = ft_getline(&str);
// 	// char * line4 = ft_getline(&str);

// 	// printf("%s",line);
// 	// printf("%s",line2);
// 	// printf("%s",line3);
// 	// printf("%s",line4);
	
// 	// free(str);
// 	// free(line);
// 	// free(line2);
// 	// free(line3);
// 	// free(line4);
// 	char * line;
// 	int i = 0;
// 	while ((line = get_next_line(fd)) != NULL && i < 3) 
// 	{
// 		printf("%d | line => %s",i,line);
// 		free(line);
// 		i++;
// 	}

// 	return (0);
// }
