/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:16:26 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 09:09:24 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_rotate(t_stack **stack_a)
{
	t_stack	*prev;
	t_stack	*current;

	if (is_empty(*stack_a) || (*stack_a)->next == NULL)
		return ;
	prev = NULL;
	current = *stack_a;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	if (prev != NULL)
		prev->next = NULL;
	current->next = *stack_a;
	*stack_a = current;
}

void	ft_rra(t_stack **stack_a)
{
	ft_rotate(stack_a);
	write(1, "rra\n", 4);
}

void	ft_rrb(t_stack **stack_b)
{
	ft_rotate(stack_b);
	write(1, "rrb\n", 4);
}

void	ft_rrr(t_stack **stack_a, t_stack **stack_b)
{
	ft_rotate(stack_a);
	ft_rotate(stack_b);
	write(1, "rrr\n", 4);
}
