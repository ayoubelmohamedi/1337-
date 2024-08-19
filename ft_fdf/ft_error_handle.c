
#include "ft_fdf.h"


void ft_error()
{
    size_t l;
    char * msg;

    msg = "Found wrong line length. Exiting."; 
    l = ft_strlen(msg); 
    write(1,msg,l);
    exit(1);
}

int is_extension_valid(char * filename)
{
    size_t len;

    len = ft_strlen(filename) - 5; 
    if (len < 5)
        return (0);
    filename -= len;
    if (ft_strncmp( filename, ".fdf" , 4))
        return (1);
    return (0);
}

int is_file_valid(char * filename)
{
	size_t cols;
	size_t c;
	char *line;
    char *tmp;
	char **split;
	int fd;
    
	cols = ft_getcols(filename);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
    c = 0;
    while (line)
    {
        while (split[cols])
	    {
		    cols++;
		    free(split[cols-1]);
	    }
        free(split);
        tmp = line;
        line = get_next_line(fd);
        free(tmp);
        if (c != cols)
            break;
    }
	close(fd);
    printf("c == cols is => %d\n", c == cols);
	return (c == cols);
}

int is_valid(char * filename)
{
    printf("1 - is_valid\n");

    if (filename && is_extension_valid(filename))
    {
        printf("inside is_valid\n");
        if (!is_file_valid(filename))
            ft_error();  
        return (0);
    }
    if (!is_extension_valid(filename))
        return (0);
    return (1);
}