/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 06:33:11 by ael-moha          #+#    #+#             */
/*   Updated: 2024/04/22 06:34:20 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <unistd.h>

void	ft_bit_handler(int sig);
void	ft_sendbits(int pid, char c);

void	ft_ack_mesage(int pid);
void	ft_confirm(int pid);

#endif