/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:11:07 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 16:34:49by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdio.h>


void ft_sort_div5(t_stack **stk_a, t_stack **stk_b)
{
    int min;
	int dist;
    int left;
	int diff;

	min = 0;
	left = ft_stacklen(*stk_a); 
    while (left > 5)
    {
        dist = ft_getdistance(*stk_a, min);
		diff = left - dist;

        if (dist <= (left / 2))
			while (dist--)
            	ft_ra(stk_a);
        else
			while (diff--)
            	ft_rra(stk_a);
          ft_pb(stk_a, stk_b);
        left--;
        min++;
    }
	sort_5(stk_a, stk_b);
    while (*stk_b)
        ft_pa(stk_a, stk_b);
}

static void move_to_top(t_stack **stk, int index, size_t size)
{
	t_stack * head;
	int		i;
	int		is_stk_b;

	head = *stk;
	i = 0;
	is_stk_b = 0;
	if (index < 0)
	{
		is_stk_b = 1;
		index *= -1;
	}
	while (head && head->index != index)
	{
		head = head->next;
		i++;
	}
	while (i-- <= (size / 2 + (size % 2 != 0)))
		if (is_stk_b)
			ft_rb(stk);
		else
			ft_ra(stk);
}

static int ft_max_or_min(t_stack *stk_a, t_stack *stk_b)
{
	t_stack * head;
	int is_min;
	int is_max;

	is_min = 1;
	is_max = 1;
	head = stk_b;
	while (head)
	{
		if (head->index > stk_a->index)
			is_max = 0;
		if (head->index < stk_a->index)
			is_min = 0;
		head = head->next;
	}
	return (is_min || is_max);
}


static int cost_to_top(t_stack *stk, int nbr, size_t size)
{
	t_stack * head;
	int 	res;	
	int		index;

	head = stk;
	index = 0;
	if (nbr < 0)
		nbr = ft_getmin(stk, -nbr);
	while (head->index != nbr)
	{
		index++;
		head = head->next;
	}
	if (index <= (size / 2 + (size % 2 != 0)))
		res = head->index;
	else
		res = (size - index) + 1;	
	return res;
}


static int best_cost(t_stack *stk_a, t_stack *stk_b, size_t l1, size_t l2)
{
	t_stack *head;
	t_stack *head2;
	int 	cost;
	int		min;
	int		tmp;
	int		index;

	head = stk_a;
	head2 = stk_b;
	tmp = INT_MAX;
	while (head)
	{
		cost = cost_to_top(stk_a, head->index, l1);	
		min = head2->index;
		while (head2)
		{
			if (head2->index < head->index && head2->index < min)
				min = head2->index;
			head2 = head2->next;
		}
		cost += cost_to_top(stk_a, head2->index * (-1),l2);
		head = head->next;
		if (cost < tmp)
		{
			tmp = cost;
			index = head->index;
		}
	}
	return (index);
}

static void ft_move_to_b(t_stack **stk_a, t_stack **stk_b)
{
	int n1, cost, tmp;
	t_stack *head, *head2;
	size_t l1, l2;
	int index;
	int next_index;

	head = *stk_a;
	head2 = *stk_b;
	// n would be above to its smallest value in n2 in stk_b
	l1 = ft_stacklen(*stk_a);	
	l2 = ft_stacklen(*stk_b);	
	index = best_cost(*stk_a, head2, l1, l2);
	next_index = ft_getmin(*stk_b,index);
	move_to_top(stk_b,next_index, l2);
	move_to_top(stk_a, index, l1);
	ft_pb(stk_a, stk_b);
}

 static void ft_move_to_a(t_stack **stk_a, t_stack **stk_b)
 {

 }

void ft_sort_turk(t_stack **stk_a, t_stack **stk_b)
{
	int size;

	size = ft_stacklen(*stk_a);   
	ft_pb(stk_a, stk_b);	
	ft_pb(stk_a, stk_b);
	while (size-- > 3)
	{
		if (ft_max_or_min(*stk_a, *stk_b))
			ft_pb(stk_a, stk_b);
		else
			ft_move_to_b(stk_a, stk_b);
	}
	sort_3(stk_a);
	while(*stk_b)
		ft_move_to_a(stk_a, stk_b);
}

static int	ft_max_bits(t_stack **stack)
{
	t_stack	*head;
	int		max;
	int		max_bits;

	head = *stack;
	max = head->index;
	max_bits = 0;
	while (head)
	{
		if (head->index > max)
			max = head->index;
		head = head->next;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}


void	ft_radix_sort(t_stack **stk_a, t_stack **stk_b)
{
	t_stack	*h_a;
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	max_bits;

	i = 0;
	size = ft_stacklen(*stk_a);
	max_bits = (size_t)ft_max_bits(stk_a);
	h_a = *stk_a;
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			h_a = *stk_a;
			if (((h_a->index >> i) & 1) == 1)
				ft_ra(stk_a);
			else
				ft_pb(stk_a, stk_b);
		}
		while (ft_stacklen(*stk_b) != 0)
			ft_pa(stk_a, stk_b);
		i++;
	}
}
