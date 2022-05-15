/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_semaphores.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:27:34 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/15 14:02:18 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static int	set_counter_semaphores(t_args *args)
{
	ssize_t	i;
	char	name[4];

	i = 0;
	name[0] = 'c';
	name[1] = 'o';
	name[3] = '\0';
	while (i < args->num_philo)
	{
		name[2] = (char)i + 48;
		args->counter[i] = sem_open(name, O_CREAT | O_EXCL, 0660, 0);
		if (args->counter[i] == SEM_FAILED)
		{
			write(2, "set_semaphores: counter open\n", 29);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_counter(t_args *args)
{
	if (args->num_loops <= 0)
		return (0);
	args->counter = NULL;
	args->counter = (sem_t **)malloc(sizeof (sem_t *) * args->num_philo);
	if (args->counter == NULL)
	{
		write(2, "init_counter: malloc\n", 21);
		return (1);
	}
	ft_memset((args->counter), 0, sizeof(sem_t *) * args->num_philo);
	if (set_counter_semaphores(args))
		return (1);
	return (0);
}

static int	set_semaphores_some(t_args *args)
{
	args->forks = sem_open("forks", O_CREAT | O_EXCL, 0660, 0);
	if (args->forks == SEM_FAILED)
	{
		write(2, "set_semaphores: forks open\n", 27);
		return (1);
	}
	args->sem_death = sem_open("death", O_CREAT | O_EXCL, 0660, 1);
	if (args->sem_death == SEM_FAILED)
	{
		write(2, "set_semaphores: sem_death open\n", 31);
		return (1);
	}
	args->sem_philo = sem_open("philo", O_CREAT, 0660, 1);
	if (args->sem_philo == SEM_FAILED)
	{
		write(2, "set_semaphores: sem_philo open\n", 31);
		return (1);
	}
	return (0);
}

int	set_semaphores(t_args *args)
{
	unlink_semaphores(*args);
	if (set_semaphores_some(args))
		return (1);
	args->sem_print = sem_open("print", O_CREAT, 0660, 1);
	if (args->sem_print == SEM_FAILED)
	{
		write(2, "set_semaphores: sem_print open\n", 31);
		return (1);
	}
	args->sem_start = sem_open("start", O_CREAT, 0660, 1);
	if (args->sem_start == SEM_FAILED)
	{
		write(2, "set_semaphores: sem_start open\n", 31);
		return (1);
	}
	if (init_counter(args))
		return (1);
	return (0);
}
