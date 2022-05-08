/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:26:48 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 18:26:55 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	send_start_philos(t_philo_args *philo_args, t_id_store *pthread_ids)
{
	ssize_t			i;

	i = 0;
	pthread_mutex_lock(&(philo_args->mutex_fork[0]));
	while (i < philo_args->args->num_philo)
	{
		pthread_mutex_lock(&(philo_args->mutex_philo));
		philo_args->philo = i;
		if (pthread_create(&(pthread_ids->philo_ids[i]), NULL, \
							&thread_philo, philo_args))
		{
			perror("send_start_philos: pthread_create");
			return (1);
			//gestionar exits
		}
		i++;
	}
	return (0);
}
