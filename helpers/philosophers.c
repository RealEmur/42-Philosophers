/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/29 14:45:08 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		get_next_index(int	philos_count, int index)
{
	if (index == philos_count - 1)
		return (0);
	return (index + 1);
}

void	take_forks(t_philosopher *philo, t_philosopher *target_philo, int index)
{
		if (index % 2)
		{
			pthread_mutex_lock(&philo->fork);
			print_action(index, ACTION_FORK);
			pthread_mutex_lock(&target_philo->fork);
			print_action(index, ACTION_FORK);
		}
		else
		{
			pthread_mutex_lock(&target_philo->fork);
			print_action(index, ACTION_FORK);
			pthread_mutex_lock(&philo->fork);
			print_action(index, ACTION_FORK);
		}
}

void	eat(t_table *table, int p_index)
{ 		
	t_philosopher *const philos = table->philos;
	t_philosopher *const philo = philos + p_index;
	t_philosopher *const next_philo = \
	philos + get_next_index(table->philos_count, p_index);


	take_forks(philo, next_philo, p_index);
	print_action(p_index, ACTION_EAT);
	pthread_mutex_lock(&philo->die_at_mutex);
	philo->die_at = get_timestamp() + table->die_time;
	pthread_mutex_unlock(&philo->die_at_mutex);
	ft_wait(table->eat_time);
	print_action(p_index, ACTION_SLEEP);
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
	ft_wait(table->sleep_time);
	print_action(p_index, ACTION_THINK);
}

void	*philos_schedule(void *ptr)
{
	t_philosopher	*const	philo = ptr;
	t_table			*const	table = philo->table;
	
	while (1)
	{
		pthread_mutex_lock(&table->status_mutex);
		if (table->status == STATUS_STARTED)
		{
			pthread_mutex_unlock(&table->status_mutex);
			break;
		}
		pthread_mutex_unlock(&table->status_mutex);
	}
	while (1)
	{
		pthread_mutex_lock(&table->anyone_dead_mutex);
		pthread_mutex_unlock(&table->anyone_dead_mutex);
	}
		eat(table, philo->index);
	return (0);
}

void	dead_checker(t_table *table)
{
	t_philosopher	*philo;
	t_timestamp		timestamp;
	int		i;
	int		temp;

	while (1 && !table->anyone_dead)
	{
		printf("SA\n");
		if (table->anyone_dead)
			break ;
		timestamp = get_timestamp();
		i = 0;
		while (i < table->philos_count)
		{
			philo = table->philos + i;
			pthread_mutex_lock(&philo->die_at_mutex);
			if (philo->die_at < timestamp)
			{
				pthread_mutex_lock(&table->anyone_dead_mutex);
				table->anyone_dead = i;
				pthread_mutex_unlock(&table->anyone_dead_mutex);
				break;
			}
			pthread_mutex_unlock(&philo->die_at_mutex);
			i++;
		}
	}
	timestamp = get_timestamp();
	print_action(table->anyone_dead, ACTION_DIE);
}
