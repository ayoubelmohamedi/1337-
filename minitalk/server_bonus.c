

#include "minitalk_bonus.h"

void ft_ack_message(int seg, int pid)
{

}



int main(int ac, char **av)
{
    struct  sigaction sig ;
    int pid;
    
    if (ac != 1)
        return (0);
    pid = getpid();
    sig.sigaction = (ft_ack_message, );
    sig
    return (0);
}