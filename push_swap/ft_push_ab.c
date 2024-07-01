/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_ab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:17:17 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 09:08:11 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	push(t_stack **stack, int value)
{
	t_stack	*new_node;

	new_node = ft_new_node(value);
	if (!new_node)
		return ;
	new_node->next = *stack;
	*stack = new_node;
}

void	ft_push_back(t_stack **stack, int value)
{
	t_stack	*current;
	t_stack	*node;

	node = ft_new_node(value);
	if (*stack == NULL)
	{
		*stack = node;
	}
	else
	{
		current = *stack;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = node;
	}
}

int	pop(t_stack **stack)
{
	t_stack	*top;
	int		value;

	if (is_empty(*stack))
		return (0);
	top = *stack;
	value = top->nbr;
	*stack = top->next;
	free(top);
	return (value);
}

void	ft_pa(t_stack **stack_a, t_stack **stack_b)
{
	int	val;
	int	index;

	if (is_empty(*stack_b))
		return ;
	index = (*stack_b)->index;
	val = pop(stack_b);
	push(stack_a, val);
	(*stack_a)->index = index;
	write(1, "pa\n", 3);
}

void	ft_pb(t_stack **stack_a, t_stack **stack_b)
{
	int	val;
	int	index;

	if (is_empty(*stack_a))
		return ;
	index = (*stack_a)->index;
	val = pop(stack_a);
	push(stack_b, val);
	(*stack_b)->index = index;
	write(1, "pb\n", 3);
}
