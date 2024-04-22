/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:15:02 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/07 18:50:30 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	void	*tmp;

	newlst = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			tmp = f(lst->content);
			newnode = ft_lstnew(tmp);
			if (!newnode)
			{
				free(tmp);
				ft_lstclear(&newlst, del);
				return (NULL);
			}
			ft_lstadd_back(&newlst, newnode);
			lst = lst->next;
		}
	}
	return (newlst);
}
