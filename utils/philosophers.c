/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:26:54 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/30 17:38:21 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_action(t_table *table, int index, int action)
{
	char	*const actions[] = \
	{"is sleeping", "is eating", "is thinking", "has taken a fork", "died"};
	unsigned long long	timestamp;

	pthread_mutex_lock(&table->anyone_dead_mutex);
	if (table->anyone_dead)
	{
		pthread_mutex_unlock(&table->anyone_dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&table->anyone_dead_mutex);
	timestamp = get_timestamp();
	printf("%lld %d %s.\n", timestamp - table->sim_started_at, index + 1, actions[action]);
}


void	destroy_philo(t_philosopher *philo)
{
	//if (philo->fork)
		pthread_mutex_destroy(&philo->fork);
	//if (philo->last_eaten)
		pthread_mutex_destroy(&philo->die_at_mutex);
}

void	destroy_philos(t_philosopher *philos, int size)
{
	while(--size > -1)
		destroy_philo(philos + size);
}

int	init_philo(t_table *table, t_philosopher *philo, int index)
{
	philo->index = index;
	philo->table = table;
	philo->die_at = get_timestamp() + table->die_time;
	
	if (pthread_mutex_init(&philo->fork, NULL) 
	|| pthread_mutex_init(&philo->die_at_mutex, NULL)
	|| pthread_create(&philo->thread, NULL, philos_schedule, philo)
	|| pthread_detach(philo->thread)
	)
		return (destroy_philo(philo), 0);
	return (1);
}

int	init_philosophers(t_table *table)
{
	
	int						i;
	t_philosopher	*const philosophers = \
	(t_philosopher	*) malloc(sizeof(t_philosopher) * (table->philos_count));

	if (!philosophers)
		return (printf(MSG_MALLOC_ERR), 1);
	memset(philosophers, 0, table->philos_count * sizeof(t_philosopher));
	table->philos = philosophers;
	i = 0;
	while (i < table->philos_count)
 	{
		if (!init_philo(table, philosophers + i, i))
			return (destroy_philos(philosophers, i + 1), 1);	
		i++;
	}
	return (1);	
}