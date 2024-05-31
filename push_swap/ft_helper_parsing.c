
#include "ft_push_swap.h"


static int is_delim(char c, const char *delim) 
{
    while (*delim)
    {
        if (c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

char *ft_strtok(char *str,char *delim)
{
    static char *saved_str;
    char        *token_start;
    // char        *token_end;

    if (str != NULL)
        saved_str = str;
    if (saved_str == NULL)
        return NULL;
    while (*saved_str && is_delim(*saved_str, delim))
        saved_str++;
    if (*saved_str == '\0')
    {
        saved_str = NULL;
        return NULL;
    }
    token_start = saved_str;
    while (*saved_str && !is_delim(*saved_str, delim))
        saved_str++;
    if (*saved_str)
    {
        *saved_str = '\0';
        saved_str++;
    } else
        saved_str = NULL;
    return token_start;
}
