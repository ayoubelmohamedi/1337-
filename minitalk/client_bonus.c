/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:41:04 by ael-moha          #+#    #+#             */
/*   Updated: 2024/04/22 03:37:25 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
        usleep(400);
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
    if (pid <= 0)
        return (1);
    else 
    {
        signal(SIGUSR1,ft_confirm);
        while (av[2][i])
        {
            ft_sendbits(pid,av[2][i++]);
            signal(SIGUSR1,ft_confirm);
        }
        ft_sendbits(pid, '\n');
    }

    return (0);
}