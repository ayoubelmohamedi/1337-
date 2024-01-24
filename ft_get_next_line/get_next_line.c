
#include "get_next_line.h"

char *get_next_line(int fd)
{
    char            buffer[BUFFER_SIZE]; 
    static char     *remain; 
    char            *line;
    int             i;
    size_t          size; 

    remain = ft_strdup("");
    size = read(fd,buffer,BUFFER_SIZE);
    size  = 0;
    while (size > 0)
    {
        i = 0;
        buffer[size] = '\0';
        remain = ft_strjoin(remain, buffer);
        while (buffer[i] && (buffer[i] != '\n' || buffer[i] != '\0'))
        {
            i++;
            break;
        }
        size = read(fd,buffer,BUFFER_SIZE);
    }
    line = ft_getline(remain, sizeof(buffer));
    if (!line)
        return (0);
    return (line);
}

char *ft_getline(char *remain, size_t buffersize)
{
    char *line;
    char *tmp;
    int i;

    i = 0;
    while (remain[i] != '\n' || remain[i] != '\0')
        i++;
    line = ft_substr(remain, 0, i);
    if (!line)
        return (0);
    tmp = remain;
    remain = ft_substr(remain,i, buffersize);
    free(tmp);
    if (!remain)
    {
        free(remain);
        return (0);
    }
     return (line);
}


int main()
{
    int fd = open("text.txt", O_RDONLY);
    char * res = get_next_line(fd);
    char * res2 = get_next_line(fd);
    printf("%s",res);
    printf("%s",res2);
    return (0);
}
