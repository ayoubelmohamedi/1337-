
#include "get_next_line.h"

char *get_next_line(int fd)
{
    int static line;
    char * buff;
    int i;

    i = 0; 
    line = 0;
    if (fd < 0)
        return (NULL);
    int tot = read(fd,buff,buff_size); 
   //figure out how to use (read) to reach end of line. 
    while (buff[i] != "\0")
    {
        
    }
    buff = malloc((buff_size + 1) * sizeof(char));
    if (!buff)
        return (NULL);
    free(buff);

    return(buff);
}

int main()
{
    int fd = open("text.txt",O_RDONLY);
    char * str = get_next_line(fd);
    printf("%s\n", str);
    close(fd);

    return (0);
}

