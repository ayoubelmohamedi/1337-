

#include "ft_push_swap.h"


static int getmin(t_stack *stack) {
    int min = INT_MAX;

    while (stack) {
        if (stack->nbr < min) {
            min = stack->nbr;
        }
        stack = stack->next;
    }
    return min;
}
static int ft_getmin(t_stack *stack, int val)
{
    t_stack *head;
    int     min;

    head = stack;
    min = head->nbr;
    while (head)
    {
        head = head->next;
        if (head && head->nbr < min && head->nbr != val)
            min = head->nbr;
    }
    return (min);
}
#include <stdio.h>

void sort_4(t_stack **stack_a, t_stack **stack_b)
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

void sort_5(t_stack **stack_a, t_stack **stack_b)
{
	int	distance;

	distance = ft_getdistance(*stack_a, getmin(*stack_a));
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

void sort_3(t_stack **stack_a)
{
    t_stack	*head;
	int		min;
	int		next_min;

	head = *stack_a;
	if (is_sorted(*stack_a))
		return ;
	min = ft_getmin(*stack_a, -1);
	next_min = ft_getmin(*stack_a, min);
	if (head->nbr == min && head->next->nbr != next_min)
	{
		ft_ra(stack_a);
		ft_sa(stack_a);
		ft_rra(stack_a);
	}
	else if (head->nbr == next_min)
	{
		if (head->next->nbr == min)
			ft_sa(stack_a);
		else
			ft_rra(stack_a);
	}
	else
	{
		if (head->next->nbr == min)
			ft_ra(stack_a);
		else
		{
			ft_sa(stack_a);
			ft_rra(stack_a);
		}
	}
}

void ft_custom_sort(t_stack **stk_a, t_stack **stk_b)
{
    size_t size;

    if (is_sorted(*stk_a) || ft_stacklen(*stk_a) == 0)
        return ;
    size = ft_stacklen(*stk_a);
    if (size == 2)
        ft_sa(stk_a);
    else if (size == 3)
        sort_3(stk_a);
    else if (size == 4)
        sort_4(stk_a, stk_b);
    else if (size == 5)
        sort_5(stk_a, stk_b);	
}
