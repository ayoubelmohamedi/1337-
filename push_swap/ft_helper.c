/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:17:40 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 09:02:36 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_isdigit(char c)
{
	int	res;

	res = c >= '0' && c <= '9';
	return (res);
}

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	ft_free_stack(t_stack *stack)
{
	t_stack	*tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

int	ft_atoi(const char *nbr, t_stack *stack)
{
	int			sign;
	int			i;
	long long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (nbr[i] == '\t' || nbr[i] == '\n' || nbr[i] == ' ')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
		if (nbr[i++] == '-')
			sign *= -1;
	if (!(nbr[i] >= '0' && nbr[i] <= '9'))
		(ft_free_stack(stack), ft_error());
	while (nbr[i] && nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = (res * 10) + (nbr[i++] - '0');
		if ((res > INT_MAX || res < INT_MIN) && !(nbr[i] >= '0'
				&& nbr[i] <= '9'))
			(ft_free_stack(stack), ft_error());
	}
	if (!(nbr[i] == '\t' || nbr[i] == '\n' || nbr[i] == ' ' || nbr[i] == '\0'))
		(ft_free_stack(stack), ft_error());
	return ((int)res * sign);
}
