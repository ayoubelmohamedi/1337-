
#include "ft_philo_bonus.h"


size_t ft_strlen(char *name)
{
    size_t i;

    i = 0;
    while (name[i])
        i++;
    return (i);
}

size_t current_time_in_milliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000));
}