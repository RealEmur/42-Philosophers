/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:59 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/02 20:32:48 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_dead(t_table *table, t_philosopher *philo)
{
	return (
	(unsigned long long) fetch_data(
		&philo->die_at_mutex, &philo->die_at) < get_timestamp()
	);
}

int		check_eaten_enough(t_table *table, t_philosopher *philo)
{
	return (
		(int) fetch_data(
			&philo->times_eaten_mutex, &philo->times_eaten) >= table->must_eat
		);
}

void	start_checker(t_table *table)
{
	t_philosopher	*philo;
	int				complete_flag;
	int				dead_flag;
	int				i;
	
	while ((int) fetch_data(&table->status_mutex,  &table->status) != STATUS_ENDED)
	{
		complete_flag = table->must_eat != -1;
		dead_flag = 0;
		i = -1;
		while (++i < table->philos_count)
		{
			philo = &table->philos[i];
			if (complete_flag)
				complete_flag = check_eaten_enough(table, philo);
			if (is_dead(table, philo))
			{
				print_action(table, philo->index, ACTION_DIE);
				dead_flag = 1;
				break;
			}
		}
		if (dead_flag || complete_flag)
			end_simulation(table);
	}
}