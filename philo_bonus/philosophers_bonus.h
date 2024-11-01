/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/09/02 18:42:28 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

# define MSG_USG "Args: philo_count die_time eat_time sleep_time must_eat\n"
# define MSG_ARGS_NOT_VALID "The arguments must only contain numbers.\n"
# define MSG_TABLE "Couldn't initiliaze the struct table.\n"
# define MSG_MALLOC_ERR "Couldn't allocate memory with func malloc\n"
# define MSG_PHILO_INIT_ERR "Couldn't initialize Philosophers.\n"
# define MSG_GTOD_ERR "Error: Retrieving time from func gettimeofday().\n"
# define MSG_NEG_ARG_ERR "Error: Arguements can not be negative\n"

# define SEM_FORKS_NAME "sem_forks"
# define SEM_CHECKER_NAME "sem_checker"
# define SEM_PRINT_NAME "sem_print"
# define SEM_EAT_NAME "sem_eat"
# define SEM_DIE_AT "sem_die_at"

typedef struct timeval		t_timeval;
typedef struct s_table		t_table;
typedef unsigned long long	t_timestamp;

typedef enum e_actions
{
	ACTION_SLEEP,
	ACTION_EAT,
	ACTION_THINK,
	ACTION_FORK,
	ACTION_DIE
}	t_actions;

typedef enum e_types
{
	SIZE_32BIT,
	SIZE_64BIT,
}	t_types;

typedef struct s_philosopher
{
	int				index;
	int				times_eaten;
	pid_t			pid;	
	sem_t			*sem_eat;
	t_table			*table;
	t_timestamp		die_at;
}	t_philosopher;

typedef struct s_table
{
	int				philos_count;
	int				die_time;	
	int				sleep_time;
	int				eat_time;
	int				must_eat;
	int				end_flag;
	sem_t			*sem_forks;
	sem_t			*sem_checker;
	sem_t			*sem_print;
	sem_t			*sem_eat;
	sem_t			*sem_die_at;
	t_timestamp		sim_started_at;
	t_philosopher	*philos;
}	t_table;

int			ft_atoi(const char *str);
int			init_philosophers(t_table *table);
int			init_table(t_table *table, int size, char **args);
int			is_num(char *str);
int			m_set(pthread_mutex_t *mutex, void *addr, \
long long data, int size);
sem_t		*init_semaphore(char *name, unsigned int value);
int			destroy_semaphore(sem_t *sem, char *name);
int			start_checker(t_table *table);
void		ft_wait(int ms);
void		exit_safe(t_table *table);
void		print_action(t_table *table, int index, int action);
void		destroy_table(t_table *table);
void		destroy_philos(t_philosopher *philos, int size);
void		philos_schedule(t_table *table, t_philosopher *philo);
long long	m_fetch(pthread_mutex_t *mutex, void	*addr);
t_timestamp	get_timestamp(void);

#endif
