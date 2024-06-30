

#include "ft_push_swap.h"

static void ft_swap(t_stack **stack)
{
    int val;

   if (stack && *stack && (*stack)->next)
    {
        val = (*stack)->nbr;
        (*stack)->nbr = (*stack)->next->nbr;
        (*stack)->next->nbr = val;
    } 
    val = (*stack)->nbr;
}

void ft_sa(t_stack **stack)
{ 
    ft_swap(stack);
    write(1, "sa\n", 3);
}

void ft_sb(t_stack **stack)
{
    ft_swap(stack);
    write(1, "sb\n", 3);
}

void ft_ss(t_stack **s1, t_stack **s2)
{
    ft_swap(s1);
    ft_swap(s2);
    write(1, "ss\n", 3);
}