/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_num_loops.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:45:15 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 02:49:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static int	run_check_num_loops(t_args *args)
{
	ssize_t	i;
	char	name[4];

	name[0] = 'c';
	name[1] = 'o';
	name[3] = '\0';
	i = 0;
	while (i < args->num_philo)
	{
		name[2] = (char)i + 48;
		args->counter[i] = sem_open(name, O_RDWR);
		if (args->counter[i] == SEM_FAILED)
			perror("run_check_num_loops: sem_open");
		i++;
	}
	i = 0;
	while (i < args->num_philo)
	{
		if (sem_wait(args->counter[i]))
			perror("run_check_num_loops: sem_wait");
		i++;
	}
	return (0);
}

int	send_check_num_loops(t_args *args, pid_t *loops_id)
{
	if (args->num_loops <= 0)
	{
		*loops_id = -1;
		return (0);
	}
	*loops_id = fork();
	if (*loops_id == -1)
	{
		perror("send_check_num_loops: fork");
		return (1);
	}
	else if (*loops_id == 0)
	{
		if (run_check_num_loops(args))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		return (0);
}
