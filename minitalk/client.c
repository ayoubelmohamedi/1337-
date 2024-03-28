
#include "minitalk.h"

void sendbits(int pid, char c)
{
    int i;

    i = 0;
    while (i < 8)
    {
        if ((c & (0x01 << i)) != 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        i++;
        usleep(200);
    }
}

int main(int ac,char **argv)
{
    size_t i;

    if (ac != 3)
        return (1);
    i = 0;
    int pid = ft_atoi((const char*) argv[1]);
    while (argv[2][i])
    {
        sendbits(pid, argv[2][i++]);
    }
    sendbits(pid, '\n');
    return (0);
}