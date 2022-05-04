/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:06:18 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 21:26:35 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phtread.h>
#include <stdlib.h>
#include "philo.h"

int	free_philos_args(t_philo_args *philo_args, t_args *args)
{
	ssize_t	i;

	i = 0;
	while (i < args->num_philos)
	{
		pthread_mutex_destroy(&(philo_args->mutex_fork[i]));
		i++;
	}
	free(philo_args->mutex_fork);
	free(philo->forks);
	free(philo_args);
	return (0);
}

int	free_queue_args(t_queue_args *queue_args)
{
	pthread_mutex_destroy(queue_args->mutex);
	free(queue_args->mutex);
	log_free_all(queue_args->head_log);
	free(queue_args);
	return (0);
}

int	free_main(ssize_t *philo_lives, t_queue_args *queue_args, t_args *args)
{
	free(philo_lives);
	pthread_mutex_destroy(args->mutex_end);
	free_queue_args(queue_args);
	return (0);
}
