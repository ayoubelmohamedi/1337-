
#include "minitalk.h"

// #include <stdio.h>
// #include <signal.h>
// #include<unistd.h>

void ft_bit_handler(int signbr)
{
    static char res;
    static int i;
    if (signbr == SIGUSR1)
        res |= (1 << i++);
    else if (signbr == SIGUSR2)
        i++;
    if (i == 8)
    {
        write(1,&res,1);
        i = 0;
        res = 0;
    }
}

int  main(int ac, char **argv)
{
    if (ac != 1)
        return (1);
    int pid = getpid();
    write(1,"pid :",5);
    ft_putnbr_fd(pid,1);
    write(1,"\n",1);
    while (ac == 1)
    {
        signal(SIGUSR1, ft_bit_handler);
        signal(SIGUSR2, ft_bit_handler);
        pause();
    }
    return (0);
}