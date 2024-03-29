

#include "minitalk_bonus.h"

// void ft_confirm(int sig, siginfo_t *info, void *ucontext)
// {
//     const char *message = "character recieved\n";
//     static int pid;
//     if (!pid)
//         pid = info->si_pid;
//     if (info->si_pid != pid)
//         return ;
//     printf("message recieved by pid: %d\n",pid);
//     if (sig == SIGUSR1)
//         write(1,message,ft_strlen(message));
// }

void ft_confirm(int pid)
{
    printf("message recieved\n");
}

void ft_sendbits(int pid,char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if (c & (1 << bit))
            kill(pid, SIGUSR1);
        else 
            kill(pid,SIGUSR2);
        usleep(100);
        bit++;
    }
}

int main(int ac, char **av)
{
    int i;
    int pid;

    if (ac != 3)
        return (0);
    
    i = 0;
    pid = ft_atoi((const char*) av[1]); 
    signal(SIGUSR1,ft_confirm);
    while (av[2][i])
    {
        ft_sendbits(pid,av[2][i++]);
        signal(SIGUSR1,ft_confirm);
    } 
    ft_sendbits(pid, '\n');
    return (0);
}