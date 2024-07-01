/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 08:17:45 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 08:54:01 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

size_t	ft_stacklen(t_stack *stack)
{
	size_t	size;

	size = 0;
	while (stack != NULL)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

t_stack	*ft_new_node(int value)
{
	t_stack	*node;

	node = (t_stack *)malloc(sizeof(t_stack));
	node->nbr = value;
	node->index = -1;
	node->next = NULL;
	return (node);
}

static int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, char *delim)
{
	static char	*saved_str;
	char		*token_start;

	if (str != NULL)
		saved_str = str;
	if (saved_str == NULL)
		return (NULL);
	while (*saved_str && is_delim(*saved_str, delim))
		saved_str++;
	if (*saved_str == '\0')
	{
		saved_str = NULL;
		return (NULL);
	}
	token_start = saved_str;
	while (*saved_str && !is_delim(*saved_str, delim))
		saved_str++;
	if (*saved_str)
	{
		*saved_str = '\0';
		saved_str++;
	}
	else
		saved_str = NULL;
	return (token_start);
}
