/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/26 21:21:08 by emyildir         ###   ########.fr       */
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

typedef struct timeval t_timeval;
typedef struct s_table	t_table;
typedef unsigned long long t_timestamp;

typedef struct s_philosopher
{	
	int					index;
	t_timestamp			last_eaten;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		last_eaten_mutex;
	t_table				*table;
} t_philosopher;

typedef struct s_table
{
	int				philos_count;
	int				die_time;	
	int				sleep_time;
	int				eat_time;
	int				anyone_dead;
	t_philosopher	*philos;
	pthread_mutex_t	anyone_dead_mutex;
} t_table;


int			ft_atoi(const char *str);
int			init_philosophers(t_table *table);
int			compare_time_vals(t_timeval t1, t_timeval t2);
void		ft_wait(int	ms);
void		print_action(int index, int action);
void		handle_error(char *msg);
void		print_action(int index, int action);
void		*philos_schedule(void *ptr);
t_timestamp	get_timestamp();

#endif