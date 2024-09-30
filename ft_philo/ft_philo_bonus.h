
#ifndef FT_PHILO_BONUS_H
# define FT_PHILO_BONUS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <libft.h>

#include <semaphore.h>
#include <sys/types.h>

#include <unistd.h>
#include <sys/time.h>

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
	size_t last_eat;
    State state;
	sem_t *has_forks;
	t_all *all;
} t_philo;

typedef struct s_all
{
	int nbr_philos;
	int t_die;
	int t_eat;
	int t_sleep;
	int eat_count;
	int simulation_running;
	int ac;
	char **av;	
	size_t curr_time;
	sem_t *has_forks;
	pid_t *processes;
	t_philo *philos;
	pthread_mutex_t *critical_region;
	pthread_mutex_t *output_mtx;
} t_all;

int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);
void 	ft_err_exit(t_philo * philos);
void	declare_death(t_philo *philo);

size_t current_time_in_milliseconds();
int ft_check_simulation(t_philo *philo);

//errors
void   ft_err_exit(t_philo * philos);

#endif