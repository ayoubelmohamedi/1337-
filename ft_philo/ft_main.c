

#include <stdio.h>
#include <pthread.h>

int ft_is_nbr(char *nbr)
{
    size_t i;

    i = 0;
    while (nbr[i])
    {
        if (!ft_isdigit(nbr[i++]))
            return (0);
    }
    return (1);
}

int is_valid(char ** args)
{
    if (ft_is_nbr(args[1]))
    return (1);
}

int main(int c, char ** argv)
{
    if (c != 5 || !is_valid(argv))
        return (1);
    pthread_t  threads[ft_atoi(argv[1])];

    return (0);
}