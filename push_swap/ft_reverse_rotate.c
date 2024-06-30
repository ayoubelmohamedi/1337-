
#include "ft_push_swap.h"

void ft_rotate(t_stack **stack_a)
{
    if (is_empty(*stack_a) || (*stack_a)->next == NULL)
        return; 

    t_stack *prev = NULL;
    t_stack *current = *stack_a;

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

void ft_rra(t_stack **stack_a)
{
    ft_rotate(stack_a);
    write(1,"rra\n",4);
}

void ft_rrb(t_stack **stack_b)
{
    ft_rotate(stack_b);
    write(1,"rrb\n",4);
}

void ft_rrr(t_stack **stack_a, t_stack **stack_b)
{
    ft_rotate(stack_a);
    ft_rotate(stack_b); 
    write(1,"rrr\n",4);
}
