/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:26:54 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/18 09:10:33 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	print_action(t_table *table, int index, int action)
{
	unsigned long long	timestamp;
	char *const			actions[] = \
	{"is sleeping", "is eating", "is thinking", "has taken a fork", "died"};

	timestamp = get_timestamp();
	sem_wait(table->sem_print);
	printf("%lld %d %s\n", timestamp - table->sim_started_at, \
	index + 1, actions[action]);
	if (action != ACTION_DIE)
		sem_post(table->sem_print);
}

void	destroy_philo(t_philosopher *philo)
{
	if (philo->pid)
		kill(philo->pid, 9);
	philo->pid = 0;
}

void	destroy_philos(t_philosopher *philos, int size)
{
	while (--size > -1)
		destroy_philo(philos + size);
}

int	init_philo(t_table *table, t_philosopher *philo, int index)
{
	pid_t	pid;

	philo->index = index;
	philo->table = table;
	pid = fork();
	if (pid == -1)
		return (0);
	else if (!pid)
		philos_schedule(table, philo);
	philo->pid = pid;
	return (1);
}

int	init_philosophers(t_table *table)
{
	int						i;
	t_philosopher *const	philosophers = \
	(t_philosopher	*) malloc(sizeof(t_philosopher) * (table->philos_count));

	if (!philosophers)
		return (printf(MSG_MALLOC_ERR), 1);
	memset(philosophers, 0, table->philos_count * sizeof(t_philosopher));
	table->philos = philosophers;
	i = -1;
	while (++i < table->philos_count)
	{
		if (!init_philo(table, philosophers + i, i))
			return (destroy_philos(philosophers, i + 1), 1);
	}
	return (1);
}
