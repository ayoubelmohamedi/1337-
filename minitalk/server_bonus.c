

#include "minitalk_bonus.h"

void ft_ack_message(int seg,,int pid)
{
    static char res;
    static int i;

    if (seg)
}



int main(int ac, char **av)
{
    struct  sigaction act;
    int pid;
    
    if (ac != 1)
        return (0);
    pid = getpid();
    act.sa_sigaction = ft_ack_message;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    while(ac == 1)
    {
        sigaction(SIGUSR1, &act,NULL);
        sigaction(SIGUSR2, &act,NULL);
        pause();
    }
    sigaction(SIGUSW);
    return (0);
}