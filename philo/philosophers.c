/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:08 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/06 17:20:14 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	is_num(char *str)
{
	if (str && (*str == '-' || *str == '+'))
		str++;
	while (str && *str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

void	wait_threads(t_philosopher *philos, int size)
{
	int		i;

	i = 0;
	while (i < size)
		pthread_join(philos[i++].thread, NULL);
}

int	check_args(int size, char **args)
{
	int		i;

	if (size != 5 && size != 6)
		return (printf(MSG_USG), 0);
	i = 0;
	while (i < size)
	{
		if (ft_atoi(args[i++]) < 0)
			return (printf(MSG_NEG_ARG_ERR), 0);
		if (!is_num(args[i]))
			return (printf(MSG_ARGS_NOT_VALID), 0);
	}
	return (1);
}

int	main(int size, char **args)
{
	t_table *const	table = &(t_table){0};

	if (!check_args(size, args))
		return (1);
	if (!init_table(table, size, args))
		printf(MSG_TABLE_MUTEX);
	if (table->philos_count != 0 && table->must_eat != 0)
	{
		if (!init_philosophers(table))
		{
			destroy_table(table);
			return (printf(MSG_PHILO_INIT_ERR), 1);
		}
		start_simulation(table);
		start_checker(table);
		wait_threads(table->philos, table->philos_count);
		destroy_philos(table->philos, table->philos_count);
	}
	destroy_table(table);
	return (0);
}
