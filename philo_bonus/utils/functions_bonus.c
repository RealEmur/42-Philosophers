/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:11:09 by emyildir          #+#    #+#             */
/*   Updated: 2024/09/02 18:51:09 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

void	exit_safe(t_table *table)
{
	int						i;
	t_philosopher *const	philos = table->philos;

	i = -1;
	while (++i < table->philos_count)
		kill(philos[i].pid, SIGKILL);
	while (--i >= 0)
		waitpid(philos[i].pid, 0 ,0);
	destroy_philos(table->philos, table->philos_count);
	destroy_table(table);
	exit(EXIT_SUCCESS);
}

t_timestamp	get_timestamp(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wait(int ms)
{
	t_timestamp const	target_ms = get_timestamp() + ms;

	while (target_ms > get_timestamp())
		usleep(200);
}
















	
	



int	ft_atoi(const char *str)
{
	int		i;
	int		num;
	int		sign;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = str[i] != '-';
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (!sign)
		return (num * -1);
	return (num);
}
