
#include "ft_fdf.h"


void ft_error(char *filename, int error)
{
    size_t l;
    char * msg;
    char * msg2;
    
    msg = "Found wrong line length. Exiting.\n"; 
    msg2 = "No file ";
    l = ft_strlen(filename); 
    if (error == 0)
        write(1,msg,34);
    else if (error == 1)
    {
        write(1, msg2, 8);
        write(1, filename, l);
        write(1,"\n",1);
        exit(1);
    }
    else
    {
        write(1, "No data found.\n", 15);
        exit(1);
    }
}

int is_extension_valid(char * filename)
{
    size_t len;
    len = ft_strlen(filename); 
    if (len < 5)
        return (0);
    filename += len - 4;
    if (ft_strncmp(filename, ".fdf" , 4) == 0)
        return (1);
    return (0);
}

static size_t ft_count_elements(char ** str)
{
    size_t c;

    c = 0;
    while (str[c] != NULL)
        c++;
    return (c);
}

static void free_split(char ** str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        i++;
        free(str[i - 1]);
    }
    free(str[i]);
}

int is_file_valid(char * filename)
{
	size_t cols;
	size_t c;
	char *line;
    char *tmp;
	char **split;
	int fd;
    
	fd = open(filename, O_RDONLY);
    line = get_next_line(fd);
    if (!line )
        return (0);
	split = ft_split(line, ' ');
    c = ft_count_elements(split); 
    free_split(split);
    printf("val of c => %zu\n", c);
    while (line != NULL)
    { 
        tmp = line;
        line = get_next_line(fd);
        if (!line)
            break;
        split = ft_split(line, ' ');
        cols = ft_count_elements(split);
        free(split);
        free(tmp);
        if (c != cols)
        {
            printf("shuffed line => [%s]\n", line);
            break;
        }
    }
    free(line);
	close(fd);
    printf("cols ==  %zu\n", cols);
    printf("c ==  %zu\n", c);
	return (c == cols);
}

void is_file_empty(char *filename)
{
    int fd;
    char * line;

    fd = open(filename, O_RDONLY);
    line = get_next_line(fd);    
    close(fd);
    if (line == NULL || *line == '\n')
    {
        free(line);
        ft_error(filename, 2);
    }
}

int is_valid(char * filename)
{    
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        ft_error(filename, 1);
    }
    close(fd);
    if (filename && is_extension_valid(filename))
    {
        is_file_empty(filename);
        if (!is_file_valid(filename))
        {
            ft_error(filename, 0);
            return (0);
        }
        return (1);
    } 
    ft_error(filename, 0);
    return (0);
}