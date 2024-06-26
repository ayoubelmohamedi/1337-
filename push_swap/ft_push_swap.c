

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
    // printf("tk => %s\n ",tk);
    while (tk)
    {
        val = ft_atoi((const char *)tk, *stack);
        if (is_duplicate(*stack, val))
            ft_error();
        ft_push_back(stack, val);
        // print_stack(*stack);
        tk = ft_strtok(NULL, " ");
    }
}

int main(int ac, char **av)
{
    size_t i;
    t_stack *stack_a;
    t_stack *stack_b;

    if (ac <= 1)
        ft_error();
    i = 1;
    stack_a = NULL;
    stack_b = NULL;
    while (av[i])
        ft_parse_push(&stack_a, av[i++]); 
    // ft_radix_sort(&stack_a, &stack_b);
    // print_stack(stack_a);
    // int res = is_sorted(stack_a);
    // int dst = ft_getdistance(stack_a, 5);
    ft_custom_sort(&stack_a, &stack_b);
    // printf("distance to 5 is %d\n", dst);
    // printf("is sorted %d\n", res);
    print_stack(stack_a);
    // t_stack n2stk = {15, NULL};
    // t_stack nextstk = {9 , &n2stk};
    // t_stack stk = {11, &nextstk};

    // ft_sa(stk);
    // t_stack * ptr = &stk;
    // print_stack(ptr);
    // ft_sa(&ptr);
    // printf("size is %zu\n", ft_stacklen(stk_a));
    // print_stack(ptr);
    return (0);
}
