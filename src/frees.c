/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:06:18 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 16:46:29 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

int	cleanup_forks(ssize_t *forks, pthread_mutex_t *mutex_fork, \
					ssize_t num_philo)
{
	ssize_t	i;

	free(forks);
	i = 0;
	if (mutex_fork == NULL)
	{
		write(2, "cleanup_forks: mutex_fork == NULL\n", 34);
		return (0);
	}
	while (i < num_philo)
	{
		if (pthread_mutex_destroy(&(mutex_fork[i])))
			perror("free_forks mutex_destroy");
		i++;
	}
	free(mutex_fork);
	mutex_fork = NULL;
	return (0);
}
/*
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
*/
