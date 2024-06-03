
#include "ft_push_swap.h"

void ft_ra(t_stack **stack_a)
{
    if (is_empty(*stack_a) || (*stack_a)->next == NULL)
        return;
    // Remove the first element
    int first_value = pop(stack_a); 
    push(stack_a, first_value);
    write(1,"ra\n",3);
}

void ft_rb(t_stack **stack_b)
{
    if (is_empty(*stack_b) || (*stack_b)->next == NULL)
        return;
    int first_value = pop(stack_b); 
    push(stack_b, first_value);
    write(1,"rb\n",3);
}

void ft_rr(t_stack **stack_a, t_stack **stack_b)
{
    ft_ra(stack_a);
    ft_rb(stack_b);
    write(1,"rr\n",3);
}
