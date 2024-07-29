/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/28 21:12:19 by emyildir         ###   ########.fr       */
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
# define MSG_TABLE_MUTEX "Couldn't initiliaze mutexes for struct table.\n"
# define MSG_MALLOC_ERR "Couldn't allocate memory with func malloc\n"
# define MSG_PHILO_INIT_ERR "Couldn't initialize Philosophers.\n"
# define MSG_GTOD_ERR "Error: Retrieving time from func gettimeofday().\n"

# define ACTION_SLEEP 0
# define ACTION_EAT 1
# define ACTION_THINK 2
# define ACTION_FORK 3
# define ACTION_DIE 4

# define STATUS_PREPARING 1
# define STATUS_STARTED 2

typedef struct timeval t_timeval;
typedef struct s_table	t_table;
typedef unsigned long long t_timestamp;

typedef struct s_philosopher
{	
	int					index;
	t_timestamp			die_at;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		die_at_mutex;
	t_table				*table;
} t_philosopher;

typedef struct s_table
{
	int				philos_count;
	int				die_time;	
	int				sleep_time;
	int				eat_time;
	int				anyone_dead;
	int				status;
	t_philosopher	*philos;
	pthread_mutex_t	anyone_dead_mutex;
	pthread_mutex_t status_mutex;
} t_table;


int			ft_atoi(const char *str);
int			init_philosophers(t_table *table);
void		ft_wait(int	ms);
void		print_action(int index, int action);
void		*philos_schedule(void *ptr);
void		dead_checker(t_table *table);
t_timestamp	get_timestamp();

#endif