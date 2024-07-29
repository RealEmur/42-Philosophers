/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:08 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/28 21:17:41 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int		main(int size, char **args)
{
	t_table		*const table = &(t_table){0};

	if (size != 4 && size != 5)
		return (printf(MSG_USAGE), 1);
	table->philos_count = ft_atoi(args[1]);
	table->die_time = ft_atoi(args[2]);
	table->eat_time = ft_atoi(args[3]);
	table->anyone_dead = 0;
	table->status = STATUS_PREPARING;
	if(pthread_mutex_init(&(table->anyone_dead_mutex), NULL))
		return (printf(MSG_TABLE_MUTEX), 1);
	if (!init_philosophers(table))
		return (printf(MSG_PHILO_INIT_ERR), 1);
	pthread_mutex_lock(&table->status_mutex);
	table->status = STATUS_STARTED;
	pthread_mutex_unlock(&table->status_mutex);
	dead_checker(table);
	return (0);
}

