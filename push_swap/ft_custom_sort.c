/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:18:00 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 08:46:43 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	move(t_stack *head, t_stack **stack_a, int min)
{
	if (head->next->index == min)
		ft_ra(stack_a);
	else
	{
		ft_sa(stack_a);
		ft_rra(stack_a);
	}
}

void	sort_3(t_stack **stack_a)
{
	t_stack	*head;
	int		min;
	int		next_min;

	head = *stack_a;
	if (is_sorted(*stack_a))
		return ;
	min = ft_getmin(*stack_a, -1);
	next_min = ft_getmin(*stack_a, min);
	if (head->index == min && head->next->index != next_min)
	{
		ft_ra(stack_a);
		ft_sa(stack_a);
		ft_rra(stack_a);
	}
	else if (head->index == next_min)
	{
		if (head->next->index == min)
			ft_sa(stack_a);
		else
			ft_rra(stack_a);
	}
	else
		move(head, stack_a, min);
}

void	sort_4(t_stack **stack_a, t_stack **stack_b)
{
	int	distance;

	if (is_sorted(*stack_a))
		return ;
	distance = ft_getdistance(*stack_a, ft_getmin(*stack_a, -1));
	if (distance == 1)
		ft_ra(stack_a);
	else if (distance == 2)
	{
		ft_ra(stack_a);
		ft_ra(stack_a);
	}
	else if (distance == 3)
		ft_rra(stack_a);
	if (is_sorted(*stack_a))
		return ;
	ft_pb(stack_a, stack_b);
	sort_3(stack_a);
	ft_pa(stack_a, stack_b);
}

void	sort_5(t_stack **stack_a, t_stack **stack_b)
{
	int	distance;

	distance = ft_getdistance(*stack_a, ft_getmin(*stack_a, -1));
	if (distance == 1)
		ft_ra(stack_a);
	else if (distance == 2)
	{
		ft_ra(stack_a);
		ft_ra(stack_a);
	}
	else if (distance == 3)
	{
		ft_rra(stack_a);
		ft_rra(stack_a);
	}
	else if (distance == 4)
		ft_rra(stack_a);
	if (is_sorted(*stack_a))
		return ;
	ft_pb(stack_a, stack_b);
	sort_4(stack_a, stack_b);
	ft_pa(stack_a, stack_b);
}

void	ft_custom_sort(t_stack **stk_a, t_stack **stk_b)
{
	size_t	size;

	size = ft_stacklen(*stk_a);
	if (is_sorted(*stk_a) || size == 0 || size == 1)
		return ;
	if (size == 2)
		ft_sa(stk_a);
	else if (size == 3)
		sort_3(stk_a);
	else if (size == 4)
		sort_4(stk_a, stk_b);
	else if (size == 5)
		sort_5(stk_a, stk_b);
}
