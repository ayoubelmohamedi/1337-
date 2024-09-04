/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:55:55 by ael-moha          #+#    #+#             */
/*   Updated: 2024/08/29 10:32:42 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
#include<unistd.h>

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock
# define DSTR pthread_mutex_destroy

typedef struct s_philo
{
	int index;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int nbr_philos;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_forl;
	bool has_fork;

} t_philo;


typedef struct s_all
{
	int eat_count;
	int nbr_philos;
	int t_die;
	int t_eat;
	int t_sleep;
	pthread_mutex_t *fork;
	t_philo *philos;
} t_all;


int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);

//errors
void   ft_err_exit(t_philo * philos);

#endif