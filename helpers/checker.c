/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:59 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/30 15:24:41 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_dead(t_table *table, t_philosopher *philo, t_timestamp timestamp)
{
	pthread_mutex_lock(&philo->die_at_mutex);
	if (philo->die_at < timestamp)
	{
		pthread_mutex_lock(&table->anyone_dead_mutex);
		table->anyone_dead = 1;
		pthread_mutex_unlock(&table->anyone_dead_mutex);
		pthread_mutex_unlock(&philo->die_at_mutex);
		print_action(table, philo->index, ACTION_DIE);
		return (1);
	}
	pthread_mutex_unlock(&philo->die_at_mutex);
	return (0);
}

int		check_eaten_enough(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->times_eaten_mutex);
	if (philo->times_eaten < table->must_eat)
		return (pthread_mutex_unlock(&philo->times_eaten_mutex), 0);
	return (pthread_mutex_unlock(&philo->times_eaten_mutex), 1);
}

void	checker(t_table *table)
{
	t_philosopher	*philo;
	t_timestamp		timestamp;
	int				meal_goal_succeed;
	int		i;

	while (1 && !table->anyone_dead)
	{
		meal_goal_succeed = 1;
		timestamp = get_timestamp();
		i = 0;
		while (i < table->philos_count)
		{
			philo = table->philos + i;
			if (is_dead(table, philo, timestamp))
				break;
			if (table->must_eat != -1)
				meal_goal_succeed = check_eaten_enough(table, philo);
			i++;
		}
		if (meal_goal_succeed && table->must_eat != -1)
			break;
	}
	if (!meal_goal_succeed)
		print_action(table, i, ACTION_DIE);
}