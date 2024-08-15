
#include "ft_fdf.h"

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

}

int is_valid(char * filename)
{
    int res;

    res = 0;
    if (filename && is_extension_valid(filename))
    {

    }
    return (res);
}