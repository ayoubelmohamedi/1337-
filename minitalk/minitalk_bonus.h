

# ifndef MINITALK_H  
# define MINITALK_H

#include "libft/libft.h"
// #include "ft_printf/ft_printf.h"
//to delete
#include <stdio.h>
#include <signal.h>
#include<unistd.h>

void    ft_bit_handler(int sig);
void	ft_sendbits(int pid, char c);

void    ft_check();
void    ft_ack_mesage(int pid);

#endif