/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:51:27 by ael-moha          #+#    #+#             */
/*   Updated: 2023/12/22 13:51:33 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *content, ...);
int		ft_handle(char spec, va_list *args);
int		ft_handle_nbr(int nbr);
int		ft_handle_usign(unsigned int nbr);
int		ft_count(int nbr);
int		ft_handle_hex(int nbr, char x);
int		ft_handle_char(int c);
int		ft_hande_str(char *str);
int		ft_handleptr(void *ptr);
int		ft_handle_perc(int perc);
void	ft_printnbr(int nbr, int size);
int		power(int base, int pow);
int		ft_strchr(char c);
int		ft_allspaces(const char *str);
int		ft_shorten(const char **str);
int     loopover(const char *ptr, va_list *args);



#endif
