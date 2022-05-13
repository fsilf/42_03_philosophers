/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:43:09 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 03:48:13 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

static int	init_pthread_philo_ids(t_id_store *pthread_ids, ssize_t num_philo)
{
	pthread_ids->philo_ids = NULL;
	pthread_ids->philo_ids = (pthread_t *)malloc(\
								sizeof (pthread_t) * num_philo);
	if (pthread_ids->philo_ids == NULL)
	{
		perror("init_pthread_philos_ids: malloc");
		return (1);
	}
	ft_memset(pthread_ids->philo_ids, 0, sizeof (pthread_t) * num_philo);
	return (0);
}

static int	wait_for_threads(t_id_store *pthread_ids, ssize_t num_philo)
{
	ssize_t	i;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(pthread_ids->philo_ids[i], NULL))
		{
			perror("wait_for_threads: pthread_join philo_ids");
			return (1);
		}
		i++;
	}
	if (pthread_join(pthread_ids->get_time_id, NULL))
	{
		perror("wait_for_threads: pthread_join get_time_id");
		return (1);
	}
	return (0);
}

int	set_threads(t_args *args)
{
	t_id_store		pthread_ids;

	if (init_pthread_philo_ids(&pthread_ids, args->num_philo))
	{
		free(pthread_ids.philo_ids);
		return (1);
	}
	if (send_get_time(args, &(pthread_ids.get_time_id)))
	{
		free(pthread_ids.philo_ids);
		return (1);
	}
	if (send_start_philos(args, &pthread_ids))
	{
		free(pthread_ids.philo_ids);
		return (1);
	}
	if (wait_for_threads(&pthread_ids, args->num_philo))
	{
		free(pthread_ids.philo_ids);
		return (1);
	}
	free(pthread_ids.philo_ids);
	return (0);
}
