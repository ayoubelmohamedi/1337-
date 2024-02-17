


#include <stdio.h>
#include "get_next_line.h"


int main()
{
    static char *remain;

    if (!remain)
        remain = ft_strdup("remain");
    char * tmp = remain;
    char * line = (char *)ft_strjoin(remain, " + added values\0");
    free(tmp);
    printf("line => %s\n", line);
    free(line);
    return (0);
}