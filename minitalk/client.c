
#include "minitalk.h"


void	ft_sendbits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)))
            kill(pid,SIGUSR1);
		else
            kill(pid,SIGUSR2);
        usleep(100);
		bit++;
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
        ft_sendbits(pid, argv[2][i++]);
    }
    ft_sendbits(pid, '\n');
    return (0);
}