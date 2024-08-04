/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/04 12:56:04 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	do_action(t_table *table, int index, int action, int time)
{
	if ((int) m_fetch(&table->status_mutex, &table->status) == STATUS_ENDED)
		return ;
	print_action(table, index, action);
	ft_wait(time);
}

void	take_fork(t_table *table, pthread_mutex_t *fork, int p_index)
{
	pthread_mutex_lock(fork);
	do_action(table, p_index, ACTION_FORK, 0);
}

int	philos_routine(t_table *table, int p_index)
{
	t_philosopher *const	philos = table->philos;
	t_philosopher *const	philo = philos + p_index;
	t_philosopher *const	next_philo = philos + \
	((p_index + table->philos_count - 1) % table->philos_count);

	if (philo == next_philo)
		return (0);
	if (p_index % 2)
		take_fork(table, &next_philo->fork, p_index);
	take_fork(table, &philo->fork, p_index);
	if (p_index % 2 == 0)
		take_fork(table, &next_philo->fork, p_index);
	m_set(&philo->die_at_mutex, &philo->die_at, \
	get_timestamp() + table->die_time, SIZE_64BIT);
	m_set(&philo->times_eaten_mutex, &philo->times_eaten, \
	(unsigned long long) m_fetch(&philo->times_eaten_mutex, \
	&philo->times_eaten) + 1, SIZE_64BIT);
	do_action(table, p_index, ACTION_EAT, table->eat_time);
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
	do_action(table, philo->index, ACTION_SLEEP, table->sleep_time);
	do_action(table, philo->index, ACTION_THINK, 0);
	return (1);
}

void	*philos_schedule(void *ptr)
{
	t_philosopher *const	philo = ptr;
	t_table *const			table = philo->table;

	while ((int) m_fetch(&table->status_mutex, \
	&table->status) == STATUS_PREPARING)
		;
	while ((int) m_fetch(&table->status_mutex, \
	&table->status) == STATUS_STARTED)
	{
		philos_routine(table, philo->index);
	}
	return (0);
}
