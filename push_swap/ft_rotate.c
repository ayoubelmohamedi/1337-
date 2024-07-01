/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:16:21 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 09:09:45 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_stack	*ft_lstlast(t_stack *head)
{
	t_stack	*tmp;

	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}

void	ft_ra(t_stack **stack_a)
{
	int	index;
	int	first_value;

	if (is_empty(*stack_a) || (*stack_a)->next == NULL)
		return ;
	index = (*stack_a)->index;
	first_value = pop(stack_a);
	ft_push_back(stack_a, first_value);
	ft_lstlast(*stack_a)->index = index;
	write(1, "ra\n", 3);
}

void	ft_rb(t_stack **stack_b)
{
	int	index;
	int	first_value;

	if (is_empty(*stack_b) || (*stack_b)->next == NULL)
		return ;
	index = (*stack_b)->index;
	first_value = pop(stack_b);
	ft_push_back(stack_b, first_value);
	ft_lstlast(*stack_b)->index = index;
	write(1, "rb\n", 3);
}

void	ft_rr(t_stack **stack_a, t_stack **stack_b)
{
	ft_ra(stack_a);
	ft_rb(stack_b);
	write(1, "rr\n", 3);
}
