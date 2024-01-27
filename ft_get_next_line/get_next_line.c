
#include "get_next_line.h"

char *get_next_line(int fd)
{
    char            buffer[(size_t)BUFFER_SIZE]; 
    static char     *remain; 
    char            *tmp;
    char            *line;
    size_t           i;
    size_t          size; 

    if (!remain)
        remain = ft_strdup("");
    size = read(fd,buffer,BUFFER_SIZE);
    while (size > 0)
    {
        i = 0;
        buffer[size] = '\0';

        tmp = ft_strjoin(remain, buffer);
        free(remain);
        remain = tmp;
        while (buffer[i] && (buffer[i] != '\n' && buffer[i] != '\0'))
            i++;
        if (buffer[i] == '\n')
            break;
        size = read(fd,buffer,BUFFER_SIZE);
    }
    if (ft_strlen(remain) == 0)
    {
        free(remain);
        return (NULL);
    }
    line = ft_getline(&remain);
    if (!line)
        return (0);
    return (line);
}

char *ft_getline(char **remain)
{
    char *line;
    char *tmp;
    size_t i;
    size_t j;

    i = 0;
    while (remain[0][i] && remain[0][i] != '\n' && remain[0][i] != '\0')
        i++; 
    line = ft_substr(remain[0], 0, i);
    if (!line)
        return (0);
    j = i + 1;
    while (remain[0][j])
        j++;
    tmp = ft_substr(*remain,i + 1, j);
    free(*remain);
    *remain = tmp;
    return (line);
}

int main()
{
    int fd = open("text.txt", O_RDONLY);
    char * res = get_next_line(fd);
    printf("RES 1 = %s\n",res);
    printf("-----------\n");
    char * res2 = get_next_line(fd);
    printf("RES 2 = %s\n",res2);
    printf("-----------\n");
    char * res3 = get_next_line(fd);
    printf("RES 3 = %s\n",res3);
    printf("-----------\n");
    char * res4 = get_next_line(fd);
    printf("RES 4 = %s\n",res4);   
    printf("-----------\n");
    char * res5 = get_next_line(fd);
    printf("RES 5 = %s\n",res5);

    free(res);
    free(res2);
    free(res3);
    free(res4);
    return (0);
}