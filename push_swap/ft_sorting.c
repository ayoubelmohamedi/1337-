

#include "ft_push_swap.h"


int ft_getmin(t_stack *stack, int val)
{
    t_stack *head;
    int     min;

    head = stack;
    min = head->index;
    while (head)
    {
        head = head->next;
        if (head && head->index < min && head->index != val)
            min = head->index;
    }
    return (min);
}

int is_sorted(t_stack *stack)
{
    t_stack *head;

    head = stack;
    while(head && head->next)
    {
        if (head->nbr > head->next->nbr)
            return (0);
        head = head->next;
    }
    return (1);
}

int ft_getdistance(t_stack *stack, int val)
{
   t_stack *head;
   int     distance;

   distance = 0;
   head = stack;
   while (head)
   {
       if (head->index == val)
           break;
       head = head->next;
       distance++;
   }
   return (distance);
}
