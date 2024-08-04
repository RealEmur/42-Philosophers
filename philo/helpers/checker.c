/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:59 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/04 15:12:04 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_dead(t_table *table, t_philosopher *philo)
{
	const t_timestamp	current_ts = get_timestamp();
	const t_timestamp	die_at = \
	m_fetch(&philo->die_at_mutex, &philo->die_at);

	return ((die_at == 0
			&& (t_timestamp) current_ts - table->sim_started_at \
		> (t_timestamp) table->die_time)
		|| (die_at > 0 && die_at < current_ts));
}

int	check_eaten_enough(t_table *table, t_philosopher *philo)
{
	return (
		(int) m_fetch(
			&philo->times_eaten_mutex, &philo->times_eaten) >= table->must_eat
	);
}

void	start_checker(t_table *table)
{
	t_philosopher	*philo;
	int				complete_flag;
	int				dead_flag;
	int				i;

	while ((int) m_fetch(&table->status_mutex, \
	&table->status) == STATUS_STARTED)
	{
		complete_flag = table->must_eat != -1;
		dead_flag = 0;
		i = -1;
		while (++i < table->philos_count && !dead_flag)
		{
			philo = &table->philos[i];
			if (complete_flag)
				complete_flag = check_eaten_enough(table, philo);
			dead_flag = is_dead(table, philo);
		}
		if (dead_flag || complete_flag)
			end_simulation(table);
		if (dead_flag)
			print_action(table, philo->index, ACTION_DIE);
	}
}
