/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:01:19 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/18 09:14:28 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	destroy_table(t_table *table)
{
	sem_unlink(SEM_CHECKER_NAME);
	sem_unlink(SEM_EAT_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_DIE_AT);
	if (table->sem_forks)
		sem_close(table->sem_forks);
	if (table->sem_print)
		sem_close(table->sem_print);
	if (table->sem_checker)
		sem_close(table->sem_checker);
	if (table->sem_eat)
		sem_close(table->sem_eat);
	if (table->sem_die_at)
		sem_close(table->sem_die_at);
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
	table->sem_forks = init_semaphore(SEM_FORKS_NAME, table->philos_count);
	table->sem_checker = init_semaphore(SEM_CHECKER_NAME, 0);
	table->sem_print = init_semaphore(SEM_PRINT_NAME, 1);
	table->sem_eat = init_semaphore(SEM_EAT_NAME, 0);
	table->sem_die_at = init_semaphore(SEM_DIE_AT, 1);
	if (!table->sem_forks || !table->sem_checker || !table->sem_print
		|| !table->sem_eat || !table->sem_die_at)
		return (destroy_table(table), 0);
	table->sim_started_at = get_timestamp();
	return (1);
}
