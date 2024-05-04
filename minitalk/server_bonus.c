/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:40:54 by ael-moha          #+#    #+#             */
/*   Updated: 2024/05/02 18:47:49 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_ack_message(int sig, siginfo_t *info, void *ucontext)
{
	static char	res;
	static int	bit;

	(void)ucontext;
	if (sig == SIGUSR1)
		res |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &res, 1);
		if (res == '\0')
			kill(info->si_pid, SIGUSR1);
		bit = 0;
		res = 0;
	}
}

int	main(void)
{
	struct sigaction	act;
	int					pid;

	pid = getpid();
	write(1, "pid :", 5);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	act.sa_sigaction = ft_ack_message;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
