/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:43:09 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 19:11:13 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

static int	init_pthread_philo_ids(ssize_t num_philo, t_id_store *pthread_ids)
{
	pthread_ids->philo_ids = NULL;
	pthread_ids->philo_ids = (pthread_t *)malloc(
								sizeof (pthread_t) * num_philo);
	if (pthread_ids->philo_ids == NULL)
	{
		perror("send_start_philos: malloc");
		return (1);
		//gestionar exits
	}
	ft_memset(pthread_ids->philo_ids, 0, sizeof (pthread_t) * num_philo);
	return (0);
}

static int	wait_for_philo_threads(t_id_store *pthread_ids, ssize_t num_philo)
{
	ssize_t	i;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(pthread_ids->philo_ids[i], NULL))
		{
			perror("wait_for_philo: pthread_join");
			return (1);
		}
		i++;
		printf("finish one\n");
	}
	return (0);
}

int	wait_for_threads(t_id_store *pthread_ids, ssize_t num_philo)
{
	if (pthread_join(pthread_ids->lives_id, NULL))
	{
		free(pthread_ids->philo_ids);
		perror("send_check_live: thread_join");
		return (1);
	}
	printf("llega aqui?\n");
	//if (pthread_join(*pthread_print_id, &resval))
	if (pthread_join(pthread_ids->print_id, NULL))
	{
		free(pthread_ids->philo_ids);
		perror("send_printing_queue: pthread_join");
		return (1);
	}
	printf("y aqui?\n");
	if (wait_for_philo_threads(pthread_ids, num_philo))
	{
		free(pthread_ids->philo_ids);
		return (1);
		//gestionar exits
	}
	printf("last one\n");
	return (0);
}

static int	send_threads(t_queue_args *queue_args, t_philo_args *philo_args,
							t_id_store	*pthread_ids)
{
	if (send_start_philos(philo_args, pthread_ids))
		return (1);
	if (send_check_lives(philo_args, queue_args, pthread_ids))
		return (1); 
	usleep(50000);
	if (send_printing_queue(queue_args, pthread_ids))
		return (1);
	return (0);
}

int	set_threads(t_queue_args *queue_args, t_philo_args *philo_args)
{
	t_id_store		pthread_ids;

	if (init_pthread_philo_ids(philo_args->args->num_philo, &pthread_ids))
		return (1);
	if (send_threads(queue_args, philo_args, &pthread_ids))
		return (1);
	if (wait_for_threads(&pthread_ids, philo_args->args->num_philo))
		return (1);
	free(pthread_ids.philo_ids);
	return (0);
}
