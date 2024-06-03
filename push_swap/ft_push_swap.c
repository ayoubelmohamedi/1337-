

#include "ft_push_swap.h"

#include "stdio.h"

void print_stack(t_stack *stack)
{
    printf("=============\n");
    printf("printing stack\n");
    size_t i;
    
    i = 0;
    while (stack)
    {
        printf("%d\n", stack->nbr);
        stack = stack->next;
        i++;
    }
    stack -= i;
}

int is_duplicate(t_stack *stack, int value) {
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
    if (tk == '\0')
        (ft_free_stack(*stack), ft_error());
    while (tk)
    {
        val = ft_atoi((const char *)tk, *stack);
        if (is_duplicate(*stack, val))
            ft_error();
        ft_push_back(stack, (int)val);
        tk = ft_strtok(NULL, " ");
    }
}

int main(int ac, char **av)
{
    size_t i;
    t_stack *stk_a;

    if (ac <= 1)
        ft_error();
    i = 1;
    while (av[i])
        ft_parse_push(&stk_a, av[i++]); 
    print_stack(stk_a);
    // t_stack n2stk = {15, NULL};
    // t_stack nextstk = {9 , &n2stk};
    // t_stack stk = {11, &nextstk};

    // ft_sa(stk);
    // t_stack * ptr = &stk;
    // print_stack(ptr);
    // ft_sa(&ptr);
    // printf("size is %zu\n", ft_stacklen(ptr));
    // print_stack(ptr);
    return (0);
}