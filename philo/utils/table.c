/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:01:19 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/05 15:40:41 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	end_simulation(t_table *table)
{
	m_set(&table->status_mutex, &table->status, STATUS_ENDED, SIZE_32BIT);
}

void	start_simulation(t_table *table)
{
	table->sim_started_at = get_timestamp();
	m_set(&table->status_mutex, &table->status, STATUS_STARTED, SIZE_32BIT);
}

void	destroy_table(t_table *table)
{
	if (pthread_mutex_lock(&table->status_mutex) != EINVAL)
		pthread_mutex_destroy(&table->status_mutex);
	if (pthread_mutex_lock(&table->print_mutex) != EINVAL)
		pthread_mutex_destroy(&table->print_mutex);
	free(table->philos);
}

int	init_table(t_table *table, int size, char **args)
{
	table->philos_count = ft_atoi(args[1]);
	table->die_time = ft_atoi(args[2]);
	table->eat_time = ft_atoi(args[3]);
	table->sleep_time = ft_atoi(args[4]);
	table->must_eat = -1;
	if (size == 6)
		table->must_eat = ft_atoi(args[5]);
	table->status = STATUS_PREPARING;
	if (pthread_mutex_init(&table->status_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (destroy_table(table), 0);
	return (1);
}
