

#include "ft_push_swap.h"

void push(t_stack **stack, int value)
{
    t_stack *new_node = ft_new_node(value);
    if (!new_node)
        return; // handle allocation failure appropriately
    new_node->next = *stack;
    *stack = new_node;
}
#include <stdio.h>
void ft_push_back(t_stack **stack, int value)
{
    printf("pushing value %d\n",value);
    t_stack *current;
    t_stack *node;
    
    node = ft_new_node(value);
    if (*stack == NULL) {
        *stack = node;
    } else {
        current = *stack;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

int pop(t_stack **stack)
{
    if (*stack == NULL)
        return 0; // or handle empty stack appropriately
    t_stack *top = *stack;
    int value = top->nbr;
    *stack = top->next;
    free(top);
    return value;
}

void	ft_pa(t_stack **stack_a, t_stack **stack_b)
{
    int val;
    
    if (is_empty(*stack_b))
        return; 
    val = pop(stack_b);
    push(stack_a, val);
    write(1,"pa\n",3);
}

void    ft_pb(t_stack **stack_b, t_stack **stack_a)
{
    int val;

    if (is_empty(*stack_a))
        return ;
    val = pop(stack_a);
    push(stack_b, val);
    write(1,"pb\n",3);

}   

int is_empty(t_stack *stack)
{
    return (stack == NULL);
}