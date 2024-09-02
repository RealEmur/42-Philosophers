/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:08 by emyildir          #+#    #+#             */
/*   Updated: 2024/08/08 21:38:25 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers_bonus.h"

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
	pid_t			checker_pid;

	if (!check_args(size, args))
		return (1);
	if (!init_table(table, size, args))
		return (printf(MSG_TABLE), 1);
	if (table->philos_count != 0 && table->must_eat != 0)
	{
		if (!init_philosophers(table))
		{
			destroy_table(table);
			return (printf(MSG_PHILO_INIT_ERR), 1);
		}
		checker_pid = fork();
		if (checker_pid == 0)
			start_checker(table);
		waitpid(checker_pid, 0, 0);
		exit_safe(table);
	}
	destroy_table(table);
	return (0);
}
