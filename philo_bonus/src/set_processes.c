/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:34:40 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 14:18:30 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "philo_bonus.h"

static int	init_process_philo_ids(t_id_store *pids, ssize_t num_philo)
{
	pids->philo_ids = NULL;
	pids->philo_ids = (pid_t *)malloc(sizeof (pid_t) * num_philo);
	if (pids->philo_ids == NULL)
	{
		perror("init_process_philo_ids");
		return (1);
	}
	ft_memset(pids->philo_ids, 0, sizeof (pid_t) * num_philo);
	return (0);
}

static int	wait_for_num_loops_process(pid_t loops_id)
{
	pid_t	wid;

	wid = -1;
	if (loops_id != -1)
	{
		kill(loops_id, SIGKILL);
		wid = waitpid(-1, NULL, 0);
		if (wid == -1)
		{
			perror("wait_for_processes: philo_ids");
			return (1);
		}
	}
	return (0);
}

static void	kill_philo_processes(t_id_store *pids, ssize_t num_philo, \
									ssize_t *once, pid_t wid)
{
	ssize_t	j;

	if (*once == 0)
	{
		j = 0;
		while (j < num_philo)
		{
			if (pids->philo_ids[j] != wid)
				kill(pids->philo_ids[j], SIGKILL);
			j++;
		}
		*once = 1;
	}
}

static int	wait_for_processes(t_id_store *pids, ssize_t num_philo)
{
	ssize_t	i;
	pid_t	wid;
	ssize_t	once;

	i = 0;
	once = 0;
	while (i < num_philo)
	{
		wid = waitpid(-1, NULL, 0);
		if (wid == -1)
		{
			perror("wait_for_processes: philo_ids");
			return (1);
		}
		kill_philo_processes(pids, num_philo, &once, wid);
		i++;
	}
	if (wait_for_num_loops_process(pids->loops_id))
		return (1);
	return (0);
}

int	set_processes(t_args *args)
{
	t_id_store	pids;

	if (init_process_philo_ids(&pids, args->num_philo))
	{
		free(pids.philo_ids);
		return (1);
	}
	if (send_check_num_loops(args, &(pids.loops_id)))
	{
		free(pids.philo_ids);
		return (1);
	}
	if (send_start_philos(args, &pids))
	{
		free(pids.philo_ids);
		return (1);
	}
	if (wait_for_processes(&(pids), args->num_philo))
	{
		free(pids.philo_ids);
		return (1);
	}
	free(pids.philo_ids);
	return (0);
}
