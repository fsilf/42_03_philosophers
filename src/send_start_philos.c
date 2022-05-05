/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:26:48 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 14:12:02 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static int	init_pthread_philo_ids(t_args *args, pthread_t **pthread_philo_ids)
{
	*pthread_philo_ids = NULL;
	*pthread_philo_ids = (pthread_t *)malloc(sizeof (pthread_t) * \
												args->num_philo);
	if (*pthread_philo_ids == NULL)
	{
		perror("send_start_philos: malloc");
		return (1);
		//gestionar exits
	}
	ft_memset(*pthread_philo_ids, 0, sizeof (pthread_t) * args->num_philo);
	return (0);
}

static int	wait_for_philo_threads(t_args *args, pthread_t *pthread_philo_id)
{
	ssize_t	i;

	i = 0;
	while (i < args->num_philo)
	{
		if (pthread_join(pthread_philo_id[i], NULL))
		{
			perror("send_start_philos: pthread_detach");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philo_threads(t_args *args, pthread_t *pthread_philo_ids, \
								t_philo_args *philo_args)
{
	ssize_t			i;
	pthread_mutex_t	mutex_philo;

	pthread_mutex_init(&mutex_philo, NULL);
	philo_args->mutex_philo = &mutex_philo;
	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_lock(&mutex_philo);
		philo_args->philo = i;
		pthread_mutex_unlock(&mutex_philo);
		if (pthread_create(&(pthread_philo_ids[i]), NULL, &thread_philo, \
								philo_args))
		{
			perror("send_start_philos: pthread_create");
			free_philos_args(philo_args, args);
			pthread_mutex_destroy(&mutex_philo);
			free(pthread_philo_ids);
			return (1);
			//gestionar exits
		}
		i++;
	}
	pthread_mutex_destroy(&mutex_philo);
	return (0);
}

int	send_start_philos(t_args *args, long unsigned *philo_lives, \
						t_queue_args *queue_args)
{
	pthread_t		*pthread_philo_ids;
	t_philo_args	*philo_args;

	if (init_pthread_philo_ids(args, &pthread_philo_ids))
		return (1);
	if (set_philo_args(args, philo_lives, queue_args, &philo_args))
		return (1);
	if (init_philo_threads(args, pthread_philo_ids, philo_args))
		return (1);
	if (wait_for_philo_threads(args, pthread_philo_ids))
	{
		free(pthread_philo_ids);
		return (1);
		//gestionar exits
	}
	free(pthread_philo_ids);
	free_philos_args(philo_args, args);
	return (0);
}
