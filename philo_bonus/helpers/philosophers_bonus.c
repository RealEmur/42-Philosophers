/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:28:45 by emyildir          #+#    #+#             */
/*   Updated: 2024/09/02 18:43:14 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

int	is_dead(t_table *table, t_philosopher *philo)
{
	const t_timestamp	current_ts = get_timestamp();

	return ((philo->die_at == 0 && current_ts - table->sim_started_at > (t_timestamp) table->die_time)
	|| (philo->die_at != 0 && philo->die_at < current_ts));
}


void	*checker(void	*ptr)
{
	t_philosopher *const	philo = ptr;
	t_table *const			table = philo->table;
	int						eaten_enough;
	
	eaten_enough = table->must_eat == -1;
	while (1)
	{
		sem_wait(table->sem_die_at);
		if (is_dead(philo->table, philo))
		{
			print_action(table, philo->index, ACTION_DIE);
			break ;
		}
		if (!eaten_enough && philo->times_eaten >= table->must_eat)
		{
			eaten_enough = 1;
			sem_post(table->sem_eat);
		}	
		sem_post(table->sem_die_at);
	}
	sem_post(table->sem_checker);
	return (0);
}

void	philos_schedule(t_table *table, t_philosopher *philo)
{
	sem_t		*const	sem_forks = table->sem_forks;
	pthread_t	thread;
	
	pthread_create(&thread, NULL, checker, philo);
	pthread_detach(thread);
	while (1)
	{
		sem_wait(sem_forks);
		print_action(table, philo->index, ACTION_FORK);
		sem_wait(sem_forks);
		print_action(table, philo->index, ACTION_FORK);
		print_action(table, philo->index, ACTION_EAT);
		sem_wait(table->sem_die_at);
		philo->die_at = get_timestamp() + table->die_time;
		philo->times_eaten++;
		sem_post(table->sem_die_at);
		ft_wait(table->eat_time);
		sem_post(sem_forks);
		sem_post(sem_forks);
		print_action(table, philo->index, ACTION_SLEEP);
		ft_wait(table->sleep_time);
		print_action(table, philo->index, ACTION_THINK);
	}
}
