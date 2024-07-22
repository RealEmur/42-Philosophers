/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:08 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/21 23:59:45 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int		main(int size, char **args)
{
	t_table		table;
	
	if (size != 4)
		return (printf(MSG_USAGE), 0);
	table.philos_count = ft_atoi(args[1]);
	table.die_time = ft_atoi(args[2]);
	table.eat_time = ft_atoi(args[3]);
	init_philosophers(&table);
	return (0);
}
