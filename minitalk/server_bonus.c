

#include "minitalk_bonus.h"

void ft_ack_message(int sig,siginfo_t *info, void *ucontext)
{
    static char res;
    static int bit;

    if (sig == SIGUSR1)
        res |= (1 << bit);
    bit++;
    if (bit == 8)
    {
        write(1,&res,1);
        kill(info->si_pid, SIGUSR1);
        bit = 0;
        res = 0;
    }
}

int main(int ac, char **av)
{
    struct  sigaction act;
    int pid;
    
    if (ac != 1)
        return (0);
    pid = getpid(); 
    write(1,"pid :",5);
    ft_putnbr_fd(pid,1);
    write(1,"\n",1);
    act.sa_sigaction = ft_ack_message;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    while(ac == 1)
    {
        sigaction(SIGUSR1, &act,NULL);
        sigaction(SIGUSR2, &act,NULL);
        pause();
    }
    return (0);
}