/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:55:55 by ael-moha          #+#    #+#             */
/*   Updated: 2024/09/14 21:47:21 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <libft.h>

#include <unistd.h>
#include <sys/time.h>

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock
# define DSTR pthread_mutex_destroy

typedef enum { THINKING, HUNGRY, EATING } State;


#define RESET "\033[0m"
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"

typedef struct s_all t_all;

typedef struct s_philo
{
	int index;
	pthread_mutex_t *my_fork;
	pthread_mutex_t *r_fork;
	t_all *all;
} t_philo;


typedef struct s_all
{
	int nbr_philos;
	int t_die;
	int t_eat;
	int t_sleep;
	int eat_count;
	int ac;
	char **av;	
	pthread_mutex_t *forks;
	pthread_t *threads;
	t_philo *philos;
	size_t curr_time;


	State *state;
	pthread_mutex_t *critical_region;
	pthread_mutex_t *output_mtx;
} t_all;

int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);

//errors
void   ft_err_exit(t_philo * philos);

#endif