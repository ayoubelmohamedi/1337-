
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
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int     is_empty(t_stack *stack);
char	**ft_split(char const *s, char c);
long     ft_atoi(const char *str);
char    *ft_strtok(char *str, char *delim);
int     str_to_int(const char *str, int *result);

//main
void ft_parse_push(t_stack **stack, char *str);


//stack helpers
void    ft_rotate(t_stack **stack_a);
size_t  ft_stacklen(t_stack *stack);
void    push(t_stack **stack, int value);
int     pop(t_stack **stack);
void    ft_error(void);


#endif