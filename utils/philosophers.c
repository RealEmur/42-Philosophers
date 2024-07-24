/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:26:54 by emyildir          #+#    #+#             */
/*   Updated: 2024/07/24 11:13:31 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_action(int index, int action)
{
	char	*const actions[] = \
	{"is sleeping", "is eating", "is thinking", "has taken a fork", "died"};
	unsigned long long	timestamp;

	timestamp = get_timestamp();
	if (!timestamp)
		handle_error(MSG_GTOD_ERR);
	printf("%lld %d %s.\n", timestamp, index, actions[action]);
}