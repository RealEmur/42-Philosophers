/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/26 21:10:24 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	eat(t_table *table, int p_index)
{ 		
	t_philosopher *const philos = table->philos;
}

void	*philos_schedule(void *ptr)
{
	t_philosopher	*const	philo = ptr;
	t_table			*const	table = philo->table;
	
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		eat(table, philo->index);
		pthread_mutex_unlock(&philo->fork);
	}
	return (0);
}

/*
void	dead_checker(t_table *table)
{
	t_philosopher	*philo;
	t_timestamp		timestamp;
	int		i;
	int		temp;

	while (1 && table->philo_dead == -1)
	{
		timestamp = get_timestamp();
		i = 0;
		while (i < table->philos_count)
		{
			philo = table->philos + i;
			pthread_mutex_lock(&philo->dead_mutex);
			if ((table->philos[i].last_eaten == 0 && table->sim_start + table->die_time < timestamp) 
			|| (table->philos[i].last_eaten  != 0 && table->philos[i].last_eaten + table->die_time < timestamp))
			{
				if (table->philo_dead == -1)
				{
					table->philo_dead = i;
					pthread_mutex_unlock(&philo->dead_mutex);
					i++;
					continue;
				}
				temp = table->philo_dead;
				pthread_mutex_lock(&table->philos[table->philo_dead].dead_mutex);
				if (table->philos[i].last_eaten < table->philos[table->philo_dead].last_eaten)
					table->philo_dead = i;
				pthread_mutex_unlock(&table->philos[temp].dead_mutex);
				
			}
			pthread_mutex_unlock(&philo->dead_mutex);
			i++;
		}
	}
	print_action(table->philo_dead, ACTION_DIE);
}
*/
