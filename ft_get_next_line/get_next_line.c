
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

char	*ft_joinfree(char **remain, char **buffer)
{
	char	*res;

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
	line = ft_substr(tmp, 0, i);
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
	char		*res;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = (char *)ft_readfile(fd, &remain);
	if (!remain)
		return (NULL);
	res = ft_getline(&remain);
	return (res);
}

char	*ft_readfile(int fd, char **res)
{
	char	*buffer;
	ssize_t	byteread;

	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!*res)
		*res = ft_strdup("");
	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread < 0 || (byteread == 0 && ft_strlen(*res) == 0))
		{
			free(*res);
			free(buffer);
			return (NULL);
		}
		buffer[byteread] = '\0';
		*res = ft_joinfree(&buffer, res);
		if (ft_strchr(*res, '\n'))
		{
			free(buffer);
			break ;
		}
	}
	if (byteread == 0)
		free(buffer);
	return (*res);
}

int	main(void)
{
	static char *remain;
	int fd = open("text.txt", O_RDONLY);

	char *res = get_next_line(fd);
	char *res2 = get_next_line(fd);
	char *res3 = get_next_line(fd);
	char *res4 = get_next_line(fd);
	char *res5 = get_next_line(fd);
	char *res6 = get_next_line(fd);

	printf("res 1= %s\n", res);
	printf("res 2= %s\n", res2);
	printf("res 3= %s\n", res3);
	printf("res 4= %s\n", res4);
	printf("res 5= %s\n", res5);
	printf("res 6=%s\n", res6);
	free(res);
	free(res2);
	free(res3);
	free(res4);
	free(res5);
	free(res6);
	close(fd);
	return (0);
}