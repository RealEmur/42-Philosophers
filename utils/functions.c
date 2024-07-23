/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:11:09 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/24 02:24:37 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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