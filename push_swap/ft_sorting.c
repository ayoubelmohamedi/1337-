

#include "ft_push_swap.h"

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
   head    = stack;
   while (head)
   {
       if (head->nbr == val)
           break;
       head = head->next;
       distance++;
   }
   return (distance);
}
