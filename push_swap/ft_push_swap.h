/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:15:54 by ael-moha          #+#    #+#             */
/*   Updated: 2024/07/01 09:15:59 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				nbr;
	int				index;
	struct s_stack	*next;
}					t_stack;

void				ft_sa(t_stack **stack);
void				ft_pa(t_stack **stack_a, t_stack **stack_b);
void				ft_pb(t_stack **stack_a, t_stack **stack_b);
void				ft_ra(t_stack **stack_a);
void				ft_rb(t_stack **stack_b);
void				ft_rr(t_stack **stack_a, t_stack **stack_b);
void				ft_rra(t_stack **stack_a);
void				ft_rrb(t_stack **stack_b);
void				ft_rrr(t_stack **stack_a, t_stack **stack_b);

// helpers
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					is_empty(t_stack *stack);
int					ft_atoi(const char *nbr, t_stack *stack);
char				*ft_strtok(char *str, char *delim);
int					str_to_int(const char *str, int *result);

// utils
int					is_sorted(t_stack *stack);
int					ft_getdistance(t_stack *stack, int val);
void				index_stack(t_stack **stack);

// sort
int					ft_getmin(t_stack *stack, int val);
void				ft_custom_sort(t_stack **stk_a, t_stack **stk_b);
void				ft_radix_sort(t_stack **stk_a, t_stack **stk_b);
void				sort_3(t_stack **stack_a);
void				sort_4(t_stack **stack_a, t_stack **stack_b);
void				sort_5(t_stack **stack_a, t_stack **stack_b);

// tobe deleted
void				print_stack(t_stack *stack);

// main
void				ft_parse_push(t_stack **stack, char *str);

// stack helpers
t_stack				*ft_new_node(int value);
t_stack				*ft_lstlast(t_stack *head);
void				ft_push_back(t_stack **stack, int value);
void				ft_rotate(t_stack **stack_a);
size_t				ft_stacklen(t_stack *stack);
void				push(t_stack **stack, int value);
int					pop(t_stack **stack);
void				ft_error(void);
void				ft_free_stack(t_stack *stack);

#endif