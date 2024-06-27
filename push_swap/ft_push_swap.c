

#include "ft_push_swap.h"
#include "stdio.h"

void print_stack(t_stack *stack)
{
    size_t i;
    
    i = 0;
    while (stack)
    {
        printf("%zu -> stack %d ", i, stack->nbr);
        stack = stack->next;
        i++;
        printf("\n");
    }
    stack -= i;
}

int is_duplicate(t_stack *stack, int value)
{
    while (stack) {
        if (stack->nbr == value) {
            return 1;
        }
        stack = stack->next;
    }
    return (0);
}

void ft_parse_push(t_stack **stack, char *str)
{
    char *tk;
    int val;
 
    tk = ft_strtok(str, " ");
    if (!tk)
        (ft_free_stack(*stack), ft_error());
    while (tk)
    {
        val = ft_atoi((const char *)tk, *stack);
        if (is_duplicate(*stack, val))
            ft_error();
        ft_push_back(stack, val);
        tk = ft_strtok(NULL, " ");
    }
}

static void sort_stack(t_stack **stack_a, t_stack **stack_b)
{
    if (ft_stacklen(*stack_a) <= 5)
        ft_custom_sort(stack_a, stack_b);
    else
        ft_radix_sort(stack_a, stack_b);
}

int main(int ac, char **av)
{
    size_t i;
    t_stack *stack_a;
    t_stack *stack_b;

    if (ac <= 1)
        return (-1); 
    i = 1;
    stack_a = NULL;
    stack_b = NULL;
    while (av[i])
        ft_parse_push(&stack_a, av[i++]); 
    if (is_sorted(stack_a) && (ft_free_stack(stack_a), 1))
        return (0);
    sort_stack(&stack_a, &stack_b); 
    (ft_free_stack(stack_a), ft_free_stack(stack_b));
    return (0);
}
