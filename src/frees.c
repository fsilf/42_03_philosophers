/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:06:18 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 16:53:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	free_philo_args(t_philo_args *philo_args)
{
	ssize_t	i;

	if (philo_args == NULL)
		return (0);
	i = 0;
	while (i < philo_args->args->num_philo)
	{
		if (pthread_mutex_destroy(&(philo_args->mutex_fork[i])))
		{
			perror("free_philo_args: mutex_destroy mutex_fork");
			break ;
		}
		i++;
	}
	if (pthread_mutex_destroy(&(philo_args->mutex_philo)))
		perror("free_philo_args: mutex_destroy mutex_philo");
	free(philo_args->mutex_fork);
	free(philo_args->forks);
	free(philo_args);
	return (0);
}

int	free_queue_args(t_queue_args *queue_args)
{
	if (queue_args == NULL)
		return (0);
	pthread_mutex_destroy(queue_args->mutex);
	free(queue_args->mutex);
	log_free_all(queue_args->head_log);
	free(queue_args);
	return (0);
}

int	free_main(long unsigned *philo_lives, t_queue_args *queue_args, \
				t_philo_args *philo_args)
{
	free(philo_lives);
	free_queue_args(queue_args);
	free_philo_args(philo_args);
	return (0);
}
