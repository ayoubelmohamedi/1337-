

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

int main()
{
    t_stack n2stk = {15, NULL};
    t_stack nextstk = {9 , &n2stk};
    t_stack stk = {11, &nextstk};

    // ft_sa(stk);
    t_stack * ptr = &stk;
    print_stack(ptr);
    ft_sa(&ptr);
    printf("size is %zu\n", ft_stacklen(ptr));
    print_stack(ptr);
    return (0);
}