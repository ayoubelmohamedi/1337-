

#include "ft_push_swap.h"

#include "stdio.h"

void print_stack(t_stack *stack)
{
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

int str_to_int(const char *str, int *result) {
    int res;
    long val;
    
    val = ft_atoi(str);
    res = val < INT_MIN || val > INT_MAX;  
    *result = (int)val;
    return (res);
}

void ft_parse_push(t_stack **stack, char *str)
{
    char *tk;
    int val;

    tk = ft_strtok(str, " ");
    while (tk)
    {
        if (!str_to_int((const char *)tk, &val))
        {
            printf("str to int\n");
            return (ft_error());
        }
        if (is_duplicate(*stack, val))
        {
            printf("str to int\n");
            return (ft_error());
        }
        push(stack, val);
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