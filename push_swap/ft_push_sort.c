/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:11:07 by ael-moha          #+#    #+#             */
/*   Updated: 2024/06/06 18:45:54 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int ft_max_bits(t_stack **stack)
{
    t_stack *head;
    int  max;
    int  max_bits;

    head = *stack;
    max = head->nbr;
    max_bits = 0;
    while (head)
    {
        if (head->nbr > max)
            max = head->nbr;
        head = head->next;
    }
    while ((max >> max_bits) != 0)
        max_bits++;
    return (max_bits);
}

#include <stdio.h>
void    ft_radix_sort(t_stack **stk_a, t_stack **stk_b)
{
    t_stack *h_a;
    size_t i;
    size_t j;
    size_t size;
    size_t max_bits;
    
    i = 0;
    size = ft_stacklen(*stk_a);
    max_bits = (size_t)ft_max_bits(stk_a);
    while (i < max_bits)
    {
        j = 0;
        while (j < size && stk_a)
        {
            h_a = *stk_a;
            if (((h_a->nbr >> i) & 1) == 1)
                ft_ra(stk_a);
            else
                ft_pb(stk_a, stk_b);
            j++;
        }
        while (ft_stacklen(*stk_b) != 0)
            ft_pa(stk_a, stk_b);
        i++;
    }
}


