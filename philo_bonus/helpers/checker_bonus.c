/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:20:55 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/18 08:58:35 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"


void	*must_eat_checker(void *ptr)
{
	t_table *const	table = ptr;
	int				count;

	count = table->philos_count;
	while (count-- > 0)
		sem_wait(table->sem_eat);
	exit(0);
	return (0);
}

int		start_checker(t_table *table)
{
	pthread_t	must_eat_thread;
	
	if (table->must_eat != -1)
	{
		pthread_create(&must_eat_thread, NULL, must_eat_checker, table);
		pthread_detach(must_eat_thread);
	}
	sem_wait(table->sem_checker);
	exit(0);
}
