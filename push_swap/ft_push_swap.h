
#ifndef FT_PUSH_SWAP_H
#define FT_PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_stack
{
    int nbr;
    struct s_stack *next;
} t_stack;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
size_t  ft_stacklen(t_stack *stack);


void    ft_sa(t_stack **stack);
void	ft_pa(t_stack **stack_a, t_stack **stack_b);
void    ft_pb(t_stack **stack_b, t_stack **stack_a);
void    ft_ra(t_stack **stack_a);
void    ft_rb(t_stack **stack_b);
void    ft_rr(t_stack **stack_a, t_stack **stack_b);
void    ft_rra(t_stack **stack_a);
void    ft_rrb(t_stack **stack_b);
void    ft_rrr(t_stack **stack_a, t_stack **stack_b);

//helpers
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void    ft_rotate(t_stack **stack_a);
void    push(t_stack **stack, int value);
int     pop(t_stack **stack);


#endif