/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/22 00:57:28 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	eat(t_philosopher *philos, int size, int index)
{
	if (index == 0)
		if (philos[1].has_fork)
			philos[1].has_fork = 0;
		else
			philos[size - 1].has_fork = 0;
	else if (index == size - 1)
		if (philos[index - 1].has_fork)
			philos[index - 1].has_fork = 0;
		else
			philos[0].has_fork = 0;
	else 
		if (philos[index - 1].has_fork)
			philos[index - 1].has_fork = 0;
		else
			philos[index + 1].has_fork = 0;
	gettimeofday(&philos[index].last_eaten, NULL);
	printf("%d Started Eating.\n", index);
	philos[index].state = STATE_EATING;
	pthread_mutex_unlock(philos[index].mutex);
	usleep(500000);
	pthread_mutex_lock(philos[index].mutex);
	printf("%d Started Thinking.\n", index);
	philos[index].state = STATE_THINKING;
	if (index == 0)
		if (!philos[1].has_fork)
			philos[1].has_fork = 1;
		else
			philos[size - 1].has_fork = 1;
	else if (index == size - 1)
		if (!philos[index - 1].has_fork)
			philos[index - 1].has_fork = 1;
		else
			philos[0].has_fork = 1;
	else 
		if (!philos[index - 1].has_fork)
			philos[index - 1].has_fork = 1;
		else
			philos[index + 1].has_fork = 1;
	pthread_mutex_unlock(philos[index].mutex);
}

int		next_to_eat(t_philosopher *philos, int size)
{
	int		i;
	int		index;

	i = 0;
	index = -1;
	while (i < size)
	{
		printf("%d - %ld %d\n", i, philos[i].last_eaten.tv_sec, philos[i].last_eaten.tv_usec);
		if ((
				((i > 0 && i < size - 1) && (philos[i - 1].has_fork ||  philos[i + 1].has_fork))
				|| (i == 0 && (philos[i + 1].has_fork || philos[size - 1].has_fork)) 
				|| (i == size - 1 && (philos[i - 1].has_fork || philos[0].has_fork)) 
			) && (index == -1 || compare_time_vals(philos[i].last_eaten, philos[index].last_eaten) < 0))
			{
				index = i;
			}
		i++;		
	}
	printf("RETURN %d\n--------------\n", index);
	return (index);
}


void	*philos_life(void *ptr)
{
	t_philosopher	*const	philo = ptr;
	t_table			*const	table = philo->table;

	while (1)
	{
		pthread_mutex_lock(philo->mutex);
		if(philo->state == STATE_THINKING 
		&& next_to_eat(table->philos, table->philos_count) == philo->index)
		{
			eat(table->philos, table->philos_count, philo->index);
		}
		else
			pthread_mutex_unlock(philo->mutex);
	}
	return (0);
}

int	init_philosophers(t_table *table)
{
	int						i;
	t_timeval				time;
	pthread_mutex_t			mutex;
	t_philosopher	*const philosophers = \
	(t_philosopher	*) malloc(sizeof(t_philosopher) * (table->philos_count));

	if (!philosophers)
		return (0);
	table->philos = philosophers;
	memset(philosophers, 0, table->philos_count * sizeof(t_philosopher));
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < table->philos_count)
	{
		philosophers[i].index = i;
		philosophers[i].has_fork = 1;
		philosophers[i].state = STATE_THINKING;
		philosophers[i].mutex = &mutex;
		philosophers[i].table = table;
		gettimeofday(&philosophers[i].last_eaten, NULL);
		pthread_create(&philosophers[i].thread, NULL, philos_life, philosophers + i);
		i++;
	}		
	i = 0;
	while (i < table->philos_count)
		pthread_join(philosophers[i++].thread, NULL);
	pthread_mutex_destroy(&mutex);
	return (1);	
}