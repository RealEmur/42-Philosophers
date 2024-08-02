/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:08 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/02 20:33:45 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	wait_threads(t_philosopher *philos, int size)
{
	int		i;

	i = 0;
	while (i < size)
		pthread_join(philos[i++].thread, NULL);
}

int		check_args(int size, char **args)
{
	if (size != 5 && size != 6)
		return (printf(MSG_USAGE), 0);
	int	i = 1;
	while (i < size)
		if (!is_all_num(args[i++]))
			return (printf(MSG_ARGS_NOT_VALID), 0);
	return (1);
}

int		main(int size, char **args)
{
	t_table		*const table = &(t_table){0};

	if (!check_args(size, args))
		return (1);
	if (!init_table(table, size, args))
		printf(MSG_TABLE_MUTEX);
	if (!init_philosophers(table))
		return (printf(MSG_PHILO_INIT_ERR), 1);
	start_simulation(table);
	start_checker(table);
	wait_threads(table->philos, table->philos_count);
	destroy_philos(table->philos, table->philos_count);
	destroy_table(table);
	return (0);
}
