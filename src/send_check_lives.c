/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 14:21:43 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	check_death(ssize_t end, pthread_mutex_t *mutex_death)
{
	pthread_mutex_lock(mutex_death);
	if (end == 1)
	{
		pthread_mutex_unlock(mutex_death);
		return (1);
	}
	pthread_mutex_unlock(mutex_death);
	return (0);
}

static void	*thread_lives(void *arg)
{
	t_philo_args	*philo;

	philo = (t_philo_args *)arg;
	while (philo->life == 0)
		usleep(50);
	while (1)
	{
		if (pthread_mutex_lock(&(philo->args->mutex_death)))
			perror("thread_lives: mutex_lock mutex_death");
		if (philo->args->end == 1)
		{
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		if (philo->args->mu_since > philo->life)
		{
			print_msg(philo, 'd');
			philo->args->end = 1;
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->args->mutex_death));
		usleep(800);
	}
	return (NULL);
}

int	send_check_lives(t_philo_args *philo)
{
	if (pthread_create(&(philo->lives_id), NULL, &thread_lives, (void *)philo))
	{
		perror("send_check_lives: pthread_create:");
		return (1);
	}
	return (0);
}
