/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/24 02:47:20 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	eat(t_philosopher *philos, int size, int index)
{ 		
	if (index == size - 1)
		pthread_mutex_lock(&philos[0].fork);
	else
		pthread_mutex_lock(&philos[index + 1].fork);
	printf("%d has taken a fork.\n", index);
	gettimeofday(&philos[index].last_eaten, NULL);
	printf("%d eating.\n", index);
	philos[index].state = STATE_EATING;
	pthread_mutex_unlock(&philos[index].fork);
	usleep(500000);
	printf("%d sleeping.\n", index);
	usleep(500000);
	printf("%d thinking.\n", index);
	philos[index].state = STATE_THINKING;
	if (index == size - 1)
		pthread_mutex_unlock(&philos[0].fork);
	else
		pthread_mutex_unlock(&philos[index + 1].fork);
}

int		next_to_eat(t_philosopher *philos, int size)
{
	int		i;
	int		index;

	i = 0;
	index = -1;
	while (i < size)
	{
		if ((
				(i == size - 1 && philos[0].state != STATE_EATING)
				|| (i != size - 1  && philos[i + 1].state != STATE_EATING) 
			) && (index == -1 || !compare_time_vals(philos[i].last_eaten, philos[index].last_eaten)))
			{
				index = i;
			}
		i++;		
	}
	return (index);
}

void	*philos_schedule(void *ptr)
{
	t_philosopher	*const	philo = ptr;
	t_table			*const	table = philo->table;
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		if(philo->state == STATE_THINKING 
		&& next_to_eat(table->philos, table->philos_count) == philo->index)
		{
			eat(table->philos, table->philos_count, philo->index);
		}
		pthread_mutex_unlock(&philo->fork);
	}
	return (0);
}

int	init_philosophers(t_table *table)
{
	int						i;
	t_philosopher	*const philosophers = \
	(t_philosopher	*) malloc(sizeof(t_philosopher) * (table->philos_count));

	if (!philosophers)
		return (0);
	memset(philosophers, 0, table->philos_count * sizeof(t_philosopher));
	table->philos = philosophers;
	i = 0;
	while (i < table->philos_count)
	{
		philosophers[i].index = i;
		philosophers[i].state = STATE_THINKING;
		philosophers[i].table = table;
		pthread_mutex_init(&philosophers[i].fork, NULL);
		gettimeofday(&philosophers[i].last_eaten, NULL);
		pthread_create(&philosophers[i].thread, NULL, philos_schedule, philosophers + i);
		i++;
	}	
	i = 0;
	while (i < table->philos_count)
		pthread_join(philosophers[i++].thread, NULL);
	return (1);	
}