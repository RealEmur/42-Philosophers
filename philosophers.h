/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:26 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/22 00:00:25 by emyildir         ###   ########.fr       */
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

# define STATE_EATING 1
# define STATE_THINKING 2
# define STATE_SLEEPING 3

typedef struct timeval t_timeval;
typedef struct s_table	t_table;

typedef struct s_philosopher
{	
	int				index;
	int				has_fork;
	int				state;
	t_timeval		last_eaten;
	pthread_mutex_t	*mutex;
	pthread_t		thread;
	t_table			*table;
} t_philosopher;

typedef struct s_table
{
	int				philos_count;
	int				die_time;	
	int				sleep_time;
	int				eat_time;
	t_philosopher	*philos;
} t_table;


int		ft_atoi(const char *str);
int		init_philosophers(t_table *table);
size_t	compare_time_vals(t_timeval t1, t_timeval t2);

#endif