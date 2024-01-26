
#include "get_next_line.h"

char *get_next_line(int fd)
{
    char            buffer[BUFFER_SIZE]; 
    static char     *remain; 
    char            *line;
    size_t           i;
    size_t          size; 

    remain = ft_strdup("");
    size = read(fd,buffer,BUFFER_SIZE);
    printf("size => %zu\n",size); 
    printf("current remain => %s\n",remain); 

    while (size > 0)
    {
        i = 0;
        buffer[size] = '\0';
        printf("size => %zu\n",size);
        printf("buffer content => %s\n",buffer);

        remain = ft_strjoin(remain, buffer);
        while (buffer[i] && (buffer[i] != '\n' && buffer[i] != '\0'))
            i++;
        printf("i => %c\n",buffer[i-1]);
        if (buffer[i] == '\n' || buffer[i] == '\0')
        {
            printf("break : i => %c\n",buffer[i]);
            break;
        }

        size = read(fd,buffer,BUFFER_SIZE);
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
    printf("getline remian => %s\n",*remain);
    while (remain[0][i] && remain[0][i] != '\n' && remain[0][i] != '\0')
        i++; 
    printf("2nd i => %zu\n",i);
    printf("len => %c\n",remain[0][i-1]);
    
    line = ft_substr(remain[0], 0, i);
    printf("line = %s\n",line);
    if (!line)
        return (0);
    j = i + 1;
    while (remain[0][j])
        j++;
    tmp = ft_substr(remain[0],i + 1, j);
    printf("tmp = %s\n",tmp);
    free(*remain);
    free(remain);
    remain = &tmp;
    free(tmp); 
    return (line);
}

int main()
{
    int fd = open("text.txt", O_RDONLY);
    char * res = get_next_line(fd);
    printf("RES 1 = %s\n",res);
    printf("-----------\n");
    char * res2 = get_next_line(fd);
    printf("RES 2 = %s",res2);
    
    return (0);
}