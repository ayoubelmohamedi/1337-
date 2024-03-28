
#include "minitalk.h"

int main(int ac,char **argv)
{
    if (ac != 3)
        return (1);
    int pid = ft_atoi((const char*) argv[1]);
    if (kill(pid, SIGUSR1) == -1)
    {
        perror("(kill)");
        return (1);
    }
    printf("signal sent");
    return (0);
2 n}