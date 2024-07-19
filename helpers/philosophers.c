/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:09:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/20 02:34:37 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_philosophers(int	count)
{
	t_timeval				time;
	t_philosopher	*const philosophers = \
	malloc(sizeof(t_philosopher) * count);

	if (!philosophers)
		return (0);
	memset(philosophers, 0, count * sizeof(t_philosopher));
	while (--count >= 0)
	{
		philosophers[count].has_fork = 1;
		philosophers[count].state = STATE_THINKING;
		gettimeofday(&time, NULL);
		philosophers[count].last_timestamp = time;
	}		

	
}