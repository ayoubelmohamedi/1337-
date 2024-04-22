/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:40:58 by ael-moha          #+#    #+#             */
/*   Updated: 2024/04/22 05:50:10 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_bit_handler(int signbr)
{
	static char	res;
	static int	i;

	if (signbr == SIGUSR1)
		res |= (1 << i++);
	else if (signbr == SIGUSR2)
		i++;
	if (i == 8)
	{
		write(1, &res, 1);
		i = 0;
		res = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "pid :", 5);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, ft_bit_handler);
	signal(SIGUSR2, ft_bit_handler);
	while (1)
		pause();
	return (0);
}
