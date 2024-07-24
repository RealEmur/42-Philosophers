/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/24 18:13:16 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		get_target_index(int size, int philo_index)
{
	if (philo_index % 2 == 0)
	{
		if (philo_index == size - 1)
			return (0);
		else 
			return (philo_index + 1);
	}
	return (philo_index - 1);
}

void	eat(t_table *table, int p_index)
{ 		
	t_philosopher *const philos = table->philos;
	const	int target = get_target_index(table->philos_count, p_index);
	
	pthread_mutex_lock(&philos[target].fork);
	print_action(p_index, ACTION_FORK);
	pthread_mutex_lock(&philos[p_index].dead_mutex);
	philos[p_index].last_eaten = get_timestamp();
	pthread_mutex_unlock(&philos[p_index].dead_mutex);
	print_action(p_index, ACTION_EAT);
	philos[p_index].state = STATE_EATING;
	ft_wait(table->eat_time);
	pthread_mutex_unlock(&philos[target].fork);
	pthread_mutex_unlock(&philos[p_index].fork);
	print_action(p_index, ACTION_SLEEP);
	ft_wait(table->sleep_time);
	print_action(p_index, ACTION_THINK);
	philos[p_index].state = STATE_THINKING;
}


int		should_eat(t_philosopher *philos, int size, int philo_index)
{
	int		target;

	target = get_target_index(size, philo_index);
	return (philos[philo_index].last_eaten <= philos[target].last_eaten);
}

/*
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
*/

void	*philos_schedule(void *ptr)
{
	t_philosopher	*const	philo = ptr;
	t_table			*const	table = philo->table;
	while (1 && table->philo_dead == -1)
	{
		pthread_mutex_lock(&philo->fork);
		if(should_eat(table->philos, table->philos_count, philo->index))
		{
			eat(table, philo->index);
		}
		pthread_mutex_unlock(&philo->fork);
	}
	return (0);
}

void	dead_checker(t_table *table)
{
	t_philosopher	*philo;
	t_timestamp		timestamp;
	int		i;
	int		temp;

	while (1 && table->philo_dead == -1)
	{
		timestamp = get_timestamp();
		i = 0;
		while (i < table->philos_count)
		{
			philo = table->philos + i;
			pthread_mutex_lock(&philo->dead_mutex);
			if ((table->philos[i].last_eaten == 0 && table->sim_start + table->die_time < timestamp) 
			|| (table->philos[i].last_eaten  != 0 && table->philos[i].last_eaten + table->die_time < timestamp))
			{
				if (table->philo_dead == -1)
				{
					table->philo_dead = i;
					pthread_mutex_unlock(&philo->dead_mutex);
					i++;
					continue;
				}
				temp = table->philo_dead;
				pthread_mutex_lock(&table->philos[table->philo_dead].dead_mutex);
				if (table->philos[i].last_eaten < table->philos[table->philo_dead].last_eaten)
					table->philo_dead = i;
				pthread_mutex_unlock(&table->philos[temp].dead_mutex);
				
			}
			pthread_mutex_unlock(&philo->dead_mutex);
			i++;
		}
	}
	print_action(table->philo_dead, ACTION_DIE);
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
	table->philo_dead = -1;
	i = 0;
	while (i < table->philos_count)
	{
		philosophers[i].index = i;
		philosophers[i].state = STATE_THINKING;
		philosophers[i].table = table;
		pthread_mutex_init(&philosophers[i].fork, NULL);
		pthread_mutex_init(&philosophers[i].dead_mutex, NULL);
		philosophers[i].last_eaten = 0;
		pthread_create(&philosophers[i].thread, NULL, philos_schedule, philosophers + i);
		i++;
	}	
	table->sim_start = get_timestamp();
	dead_checker(table);
	i = 0;
	while (i < table->philos_count)
		pthread_join(philosophers[i++].thread, NULL);
	return (1);	
}