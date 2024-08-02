/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/02 20:14:10 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MSG_USAGE "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\n"
# define MSG_ARGS_NOT_VALID "The arguments that you sent must only contain numbers.\n"
# define MSG_TABLE_MUTEX "Couldn't initiliaze mutexes for struct table.\n"
# define MSG_MALLOC_ERR "Couldn't allocate memory with func malloc\n"
# define MSG_PHILO_INIT_ERR "Couldn't initialize Philosophers.\n"
# define MSG_GTOD_ERR "Error: Retrieving time from func gettimeofday().\n"

typedef enum e_actions
{
	ACTION_SLEEP,
	ACTION_EAT,
	ACTION_THINK,
	ACTION_FORK,
	ACTION_DIE
}	t_actions;

# define ACTION_SLEEP 0
# define ACTION_EAT 1
# define ACTION_THINK 2
# define ACTION_FORK 3
# define ACTION_DIE 4

# define STATUS_ENDED 0
# define STATUS_PREPARING 1
# define STATUS_STARTED 2

typedef struct timeval t_timeval;
typedef struct s_table	t_table;
typedef unsigned long long t_timestamp;

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
} t_philosopher;

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
} t_table;


int			ft_atoi(const char *str);
int			init_philosophers(t_table *table);
int			init_table(t_table *table, int size, char **args);
int			is_all_num(char *str);
void		ft_wait(int	ms);
void		print_action(t_table *table, int index, int action);
void		start_checker(t_table *table);
void		start_simulation(t_table *table);
void		end_simulation(t_table *table);
void		*philos_schedule(void *ptr);
void		destroy_table(t_table *table);
void		destroy_philos(t_philosopher *philos, int size);
long long	fetch_data(pthread_mutex_t *mutex, void	*addr);
t_timestamp	get_timestamp();

#endif