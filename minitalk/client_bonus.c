

#include "minitalk_bonus.h"

void ft_confirm()
{
    const char *message = "character recieved\n";
    write(1,message,ft_strlen(message)) 
}




void ft_sendbits(int pid,char c)
{
    int bit;

    bit = 0;
    if (bit == 8) 
    {
        bit = 0;
        signal();
    }
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
    struct  sigaction act;

    if (ac != 1)
        return (0);
    
    i = 0;
    pid = ft_atoi((const char*) argv[1]);
    
    while (av[2][i])
    {
        ft_sendbits(pid,av[2][i++]);
        sigaction(SIGUSR1, &act,NULL);
        pause();


    }
    ft_sendbits(pid, '\n');

    return (0);
}