/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/04 12:45:18 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# define MSG_USG "Args: philo_count die_time eat_time sleep_time must_eat\n"
# define MSG_ARGS_NOT_VALID "The arguments must only contain numbers.\n"
# define MSG_TABLE_MUTEX "Couldn't initiliaze mutexes for struct table.\n"
# define MSG_MALLOC_ERR "Couldn't allocate memory with func malloc\n"
# define MSG_PHILO_INIT_ERR "Couldn't initialize Philosophers.\n"
# define MSG_GTOD_ERR "Error: Retrieving time from func gettimeofday().\n"
# define MSG_NEG_ARG_ERR "Error: Arguements can not be negative\n"

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

typedef enum e_statuses
{
	STATUS_ENDED,
	STATUS_PREPARING,
	STATUS_STARTED	
}	t_statuses;

typedef enum e_types
{
	SIZE_32BIT,
	SIZE_64BIT,
}	t_types;

typedef struct s_philosopher
{
	int					index;
	int					times_eaten;
	t_table				*table;
	t_timestamp			die_at;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		die_at_mutex;
	pthread_mutex_t		times_eaten_mutex;
}	t_philosopher;

typedef struct s_table
{
	int				philos_count;
	int				die_time;	
	int				sleep_time;
	int				eat_time;
	int				must_eat;
	int				status;
	t_timestamp		sim_started_at;
	t_philosopher	*philos;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	print_mutex;
}	t_table;

int			ft_atoi(const char *str);
int			init_philosophers(t_table *table);
int			init_table(t_table *table, int size, char **args);
int			is_num(char *str);
int			m_set(pthread_mutex_t *mutex, void *addr, \
long long data, int size);
void		ft_wait(int ms);
void		print_action(t_table *table, int index, int action);
void		start_checker(t_table *table);
void		start_simulation(t_table *table);
void		end_simulation(t_table *table);
void		destroy_table(t_table *table);
void		destroy_philos(t_philosopher *philos, int size);
void		*philos_schedule(void *ptr);
long long	m_fetch(pthread_mutex_t *mutex, void	*addr);
t_timestamp	get_timestamp(void);

#endif