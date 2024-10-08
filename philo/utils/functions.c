/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:11:09 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/06 17:47:10 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long long	m_fetch(pthread_mutex_t *mutex, void	*addr)
{
	long long	data;

	if (!pthread_mutex_lock(mutex))
	{
		data = *(long long *)addr;
		return (pthread_mutex_unlock(mutex), data);
	}
	return (0);
}

int	m_set(pthread_mutex_t *mutex, void *addr, \
long long data, int size)
{
	if (!pthread_mutex_lock(mutex))
	{
		if (size == SIZE_64BIT)
			*(unsigned long long *)addr = data;
		else if (size == SIZE_32BIT)
			*(int *)addr = data;
		return (pthread_mutex_unlock(mutex), 1);
	}
	return (0);
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
