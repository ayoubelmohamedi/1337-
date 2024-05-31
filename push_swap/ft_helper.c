

#include "ft_push_swap.h"

size_t ft_stacklen(t_stack *stack)
{
    size_t size;
    
    size = 0;
    while (stack != NULL)
    {
        size++;
        stack = stack->next;
    }
    return size;
}

void append(t_stack **stack, int value)
{
    t_stack *new_node;
    
    new_node = (t_stack *)malloc(sizeof(t_stack));
    if (!new_node)
        return; // handle allocation failure appropriately
    new_node->nbr = value;
    new_node->next = NULL;
    
    if (*stack == NULL)
        *stack = new_node;
    else
    {
        t_stack *current = *stack;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

int ft_isdigit(char c)
{
    int res;

    res = c >= '0' && c <= '9'; 
    return (res);
}

void ft_error(void)
{
    write (2, "Error\n", 6);
    exit(EXIT_FAILURE);
}

long ft_atoi(const char *str)
{
    int mod;
    long long int i;

    i = 0;
    mod = 1;
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
           || *str == '\v' || *str == '\r')
           str++;
    if (*str++ == '-')
        mod = -1;
    else if (*str == '+')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            ft_error();
        i = i * 10 + (*str - '0');
        if ((mod * i) > INT_MAX || (mod * i) < INT_MIN)
            ft_error();
        str++;
    }
    return (mod * i);
}
