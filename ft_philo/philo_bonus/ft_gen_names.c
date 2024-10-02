
#include "ft_philo_bonus.h"

char *ft_itoa(int nbr)
{
    int len;
    int tmp;
    char *res;

    len = 0;
    tmp = nbr;
    while (tmp / 10)
    {
        tmp /= 10;
        len++;
    }
    res = malloc((sizeof(char) * len) + 1);
    if (!res)
        return (NULL);
    res[len + 1] = '\0';
    while (len >= 0)
    {
        res[len--] = (nbr % 10) + '0';
        nbr /= 10;
    }
    return (res);
}

// max of i => 200
char *gen_name(int i)
{
    char *prefix;
    char *sem_name;
    char *index;
    size_t len;
    
    prefix = "meal_sem_";
    len = 9;
    index = ft_itoa(i);
    len += ft_strlen(index);
    sem_name = malloc((sizeof(char) * len) + 1);
    if (!sem_name)
        return (NULL);
    sem_name[len + 1] = '\0';
    i = -1;
    while (++i < 9)
        sem_name[i] = prefix[i];
    i -= 1;
    while (++i < len)
        sem_name[i] = index[(i - 9) % 3];
    free(index);
    return (sem_name);
}

char **philo_names(int nbr_philos)
{
    char **names;
    size_t i;

    i = -1;
    names = malloc(sizeof(char*) * nbr_philos);
    while (++i < names)
        names[i] = gen_name(i);
    return names;
}

void free_names(int nbr_philos, char **names)
{
    size_t i;

    i = -1;
    while (++i < nbr_philos)
        free(names[i]);
    free(names);
}