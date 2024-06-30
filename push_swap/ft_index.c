/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:39:57 by ael-moha          #+#    #+#             */
/*   Updated: 2024/06/30 17:03:56 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"
#include <stdio.h>

static t_stack  *ft_next_min(t_stack **stack)
{
    t_stack *head;
    t_stack *min;

    min = NULL;
    head = *stack;
    while (head)
    {
        if (head->index == -1 && (!min || head->nbr < min->nbr))
            min = head;
        head = head->next;
    }
    if (min)
        min->index = 1;
    return (min);
}


void	index_stack(t_stack **stack)
{
	t_stack	*head;
	int		index;

	index = 0;
	head = ft_next_min(stack);
	while (head)
	{
		head->index = index++;
		head = ft_next_min(stack);
	}
} 