/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:38:33 by emyildir          #+#    #+#             */
/*   Updated: 2024/09/02 18:21:19 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

sem_t	*init_semaphore(char *name, unsigned int value)
{
	sem_t	*sem;
	int		status;

	status = sem_unlink(name);
	if (status && (status == EACCES || status == ENAMETOOLONG))
		return (0);
	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
		return (0);
	return (sem);
}

int	destroy_semaphore(sem_t *sem, char *name)
{
	int		res;

	if (!sem)
		return 0;
	res = 1;
	if (sem_close(sem) == -1)
		res = 0;
	if (sem_unlink(name) == -1)
		res = 0;
	return (res);	
}