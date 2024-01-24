
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
    printf("size => %d\n",size);
    
    while (size > 0)
    {
        i = 0;
        buffer[size] = '\0';
        printf("size => %d\n",size);
        printf("buffer content %s\n",buffer);

        remain = ft_strjoin(remain, buffer);
        printf("helo\n");
        while (buffer[i] && (buffer[i] != '\n' && buffer[i] != '\0'))
            i++;
        if (buffer[i] == '\n')
            break;
        size = read(fd,buffer,BUFFER_SIZE);
    }
    line = ft_getline(remain);
    if (!line)
        return (0);
    return (line);
}

char *ft_getline(char *remain)
{
    char *line;
    char *tmp;
    size_t i;
    size_t j;

    i = 0;
    while (remain[i] != '\n' && remain[i] != '\0')
        i++;
    line = ft_substr(remain, 0, i);
    if (!line)
        return (0);
    tmp = remain;
    j = i;
    while (remain[j])
        j++;
    remain = ft_substr(remain,i, j);
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
    // int fd = open("text.txt", O_RDONLY);
    // char * res = get_next_line(fd);
    // char * res2 = get_next_line(fd);
    // printf("%s",res);
    // printf("%s",res2);
    char *line = "hello there \n it's me";
    int i = 0;
    while (line[i] != '\n' && line[i] != '\0')
        i++;
    printf("i = %d\n",i);
    char *res= ft_getline(line); 
    printf("res = %s\n",res);
    printf("line = %s\n",line);
    
    return (0);

}
