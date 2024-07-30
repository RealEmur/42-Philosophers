/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/30 17:36:05 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		get_next_index(int	philos_count, int index)
{
	if (index == 0)
		return (philos_count - 1);
	return (index - 1);
}

void	take_fork(t_table *table, pthread_mutex_t *fork, int p_index)
{
	pthread_mutex_lock(fork);
	print_action(table, p_index, ACTION_FORK);
}

void	eat(t_table *table, int p_index)
{ 		
	t_philosopher *const philos = table->philos;
	t_philosopher *const philo = philos + p_index;
	t_philosopher *const next_philo = \
	philos + get_next_index(table->philos_count, p_index);

	if (p_index % 2)
		take_fork(table, &next_philo->fork, p_index);
	take_fork(table, &philo->fork, p_index);
	if (p_index % 2 == 0)
		take_fork(table, &next_philo->fork, p_index);
	print_action(table, p_index, ACTION_EAT);
	pthread_mutex_lock(&philo->times_eaten_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
	pthread_mutex_lock(&philo->die_at_mutex);
	philo->die_at = get_timestamp() + table->die_time;
	pthread_mutex_unlock(&philo->die_at_mutex);
	ft_wait(table->eat_time);
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	*philos_schedule(void *ptr)
{
	t_philosopher	*const	philo = ptr;
	t_table			*const	table = philo->table;
	
	while (1)
	{
		pthread_mutex_lock(&table->anyone_dead_mutex);
		if (table->anyone_dead)
			pthread_mutex_unlock(&table->anyone_dead_mutex);
		pthread_mutex_unlock(&table->anyone_dead_mutex);
		eat(table, philo->index);
		print_action(table, philo->index, ACTION_SLEEP);
		ft_wait(table->sleep_time);
		print_action(table, philo->index, ACTION_THINK);
	}
	return (0);
}