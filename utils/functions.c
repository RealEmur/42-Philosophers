/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:11:09 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/24 18:31:07 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	handle_error(char *msg)
{
	printf("%s", msg);
	exit(1);
}

t_timestamp	get_timestamp()
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wait(int	ms)
{
	t_timestamp const target_ms \
	= get_timestamp() + ms;
	
	while (target_ms > get_timestamp())
	{
		usleep(200);
	}
}

int	compare_time_vals(t_timeval t1, t_timeval t2)
{
	if (t1.tv_sec != t2.tv_sec)
		return (t1.tv_sec > t2.tv_sec);
	return (t1.tv_usec > t2.tv_usec);
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