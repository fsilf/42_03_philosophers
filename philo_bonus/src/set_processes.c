/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:34:40 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 12:33:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "philo_bonus.h"

static int init_process_philo_ids(t_id_store *pids, ssize_t num_philo)
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

static int	wait_for_processes(t_id_store *pids, ssize_t num_philo)
{
	ssize_t	i;
	ssize_t	j;
	pid_t	wid;
	int		one;

	i = 0;
	one = 0;
	while (i < num_philo)
	{
		wid = waitpid(-1, NULL, 0);
		printf("wid:%d\n", wid);
		if (wid == -1)
		{
			perror("wait_for_processes: philo_ids");
			return (1);
		}
		if (one == 0)
		{
			j = 0;
			while(j < num_philo)
			{
				printf("id:%d j:%zd\n", pids->philo_ids[j], j);
				if (pids->philo_ids[j] != wid)
				{
					printf("id:%d\n", pids->philo_ids[j]);
					kill(pids->philo_ids[j], SIGKILL);
				}
				j++;
			}
			one = 1;
		}
		i++;
	}
	if (pids->loops_id != -1)
	{
		kill(pids->loops_id, SIGKILL);
		wid = waitpid(-1, NULL, 0);
		if (wid == -1)
		{
			perror("wait_for_processes: philo_ids");
			return (1);
		}
	}
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
