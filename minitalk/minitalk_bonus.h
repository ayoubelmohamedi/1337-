

# ifndef MINITALK_H  
# define MINITALK_H

#include "libft/libft.h"
#include <signal.h>
#include<unistd.h>
# include <limits.h>


void    ft_bit_handler(int sig);
void	ft_sendbits(int pid, char c);

void    ft_ack_mesage(int pid);
void ft_confirm(int pid);

#endif