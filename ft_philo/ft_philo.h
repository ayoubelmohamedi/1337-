/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:55:55 by ael-moha          #+#    #+#             */
/*   Updated: 2024/09/12 10:31:28 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock
# define DSTR pthread_mutex_destroy

typedef enum { THINKING, HUNGRY, EATING } State;

typedef struct s_all t_all;

typedef struct s_philo
{
	int index;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int is_dead;
	t_all *table;
} t_philo;


typedef struct s_all
{
	int eat_count;
	int nbr_philos;
	int t_die;
	int t_eat;
	int t_sleep;
	size_t curr_time;
	State *state;
	pthread_mutex_t *both_forks_available;
	pthread_mutex_t *critical_region;
	pthread_mutex_t *output_mtx;
	t_philo *philos;
} t_all;

int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);

//errors
void   ft_err_exit(t_philo * philos);

#endif