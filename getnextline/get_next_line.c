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

char	*ft_getline(char **remain)
{
	char *line;
	char *tmp;
	size_t i;
	
	i = 0;
	// printf("ft_getline: *remain => %s\n",*remain);
	//?? wtf is the diff btwen [0] and * ?!
	while (remain[0][i] != '\n' && remain[0][i] != '\0')
		i++;
	if (i == 0)
		return (NULL);
	tmp = *remain;
	// printf("ft_getline: tmp => %s\n",tmp);

	*remain = ft_substr(tmp,i + 1, ft_strlen(tmp) - 1);
	if (remain == NULL || *remain == 0)
	{
		free(*remain);
		*remain = NULL;
		return (NULL);
	}
	// printf("ft_getline: tmp => %s\n",tmp);

	line = ft_substr(tmp, 0, i + 1);
	// printf("ft_getline: line => %s\n",line);
	
	if (!line)
		return (NULL);
	line[i + 1] = '\0';
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char 		*buffer;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = (char *)malloc ((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ft_readfile(fd, &remain, buffer);
	free(buffer);
	if (!*remain)
	{
		// printf("getnextline: HERE\n");
		free(remain);	
		remain = NULL;
		return (NULL);
	}
	// printf("getnextline: remain => %s\n",remain);
	return (ft_getline(&remain));
}

char	*ft_readfile(int fd, char **remain, char *buffer)
{
	ssize_t		byteread;
	char		*tmp;
	
	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		// printf("bytesrread = %zd\n",byteread);
		if (byteread < 0)
			return (NULL);
		if (byteread == 0)
			break;	
		if (!*remain)
			*remain = ft_strdup("");
		buffer[byteread] = '\0';
		// printf("buffer %s\n",buffer);
		tmp = *remain;
		*remain = ft_strjoin(tmp,buffer);
		// printf("ft_readfile: remain before exit => %s",*remain);
		free(tmp);
		if (ft_strchr(buffer,'\n'))
			break;
	}
	return (*remain);
}

//int main()
//{
	//int fd = open("text.txt", O_RDONLY);
	//printf("fd = %d\n",fd);
	//char * line = get_next_line(fd);
	//char * line2 = get_next_line(fd);
	//// char * line3 = get_next_line(fd);
	//// char * line4 = get_next_line(fd);
	//// char * line5 = get_next_line(fd);


	//printf("---------------------\n");
	//printf("%s",line);
	//printf("%s",line2);
	////printf("%s",line3);
	////printf("%s",line4);
	////printf("%s",line5);

	//free(line);
	//free(line2);
	////free(line3);
	////free(line4);
	////free(line5);

	////// char * str = ft_strdup("hello\nthere\nlast");
	//// char * line = ft_getline(&str);
	//// char * line2 = ft_getline(&str);
	//// char * line3 = ft_getline(&str);
	//// char * line4 = ft_getline(&str);

	//// printf("%s",line);
	//// printf("%s",line2);
	//// printf("%s",line3);
	//// printf("%s",line4);
	
	//// free(str);
	//// free(line);
	//// free(line2);
	//// free(line3);
	//// free(line4);
	//return (0);
//}
