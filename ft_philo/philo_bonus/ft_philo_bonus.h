
#ifndef FT_PHILO_BONUS_H
# define FT_PHILO_BONUS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>

#define LOCK sem_wait
#define UNLOCK sem_post

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
	sem_t *forks;
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
	char **meal_sem_names;
	size_t curr_time;
	sem_t *forks;
	sem_t *output_sem;
	sem_t **meal_sem;
	pid_t *processes;
    pthread_t *agents;
	t_philo *philos;
} t_all;

//gen_names
char *ft_itoa(int nbr);
char *gen_name(int i);
char **philo_names(int nbr_philos);
void free_names(int nbr_philos, char **names);

//utils
size_t ft_strlen(char *name);

//parsing
int		ft_isdigit(int c);
int		ft_atoi(const char *nbr);
void 	ft_err_exit(t_philo * philos);
void	ft_parse(t_all *all, int ac, char **argv);

//routines
void	ft_usleep(size_t time_to_sleep);
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);



//ft_errors
void	declare_death(t_philo *philo);

size_t current_time_in_milliseconds();
int ft_check_simulation(t_philo *philo);

//errors
void   ft_err_exit(t_philo * philos);

#endif