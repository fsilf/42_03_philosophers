/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/09 12:02:01 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

int	check_death(ssize_t end, pthread_mutex_t *mutex_death)
{
	/*
	if (pthread_mutex_lock(&(philo->args->mutex_death)))
		perror("thread_lives: mutex_lock mutex_death");
	*/
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
	struct timeval	curr_time;

	philo = (t_philo_args *)arg;
	ft_memset(&curr_time, 0, sizeof (struct timeval));
	printf("thread_lives[%zd] with life:%ld secs, %ld usecs\n", \
			philo->philo, philo->life.tv_sec, philo->life.tv_usec);
	while (1)
	{
		if (pthread_mutex_lock(&(philo->args->mutex_death)))
			perror("thread_lives: mutex_lock mutex_death");
		if (philo->args->end == 1)
		{
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		gettimeofday(&curr_time, NULL);
		if (compare_timevals(philo->life, curr_time))
		{
			philo->args->end = 1;
			printf("tv_sec: %ld, tv_usec: %ld, philo %zd died\n", \
					curr_time.tv_sec, curr_time.tv_usec, philo->philo);
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->args->mutex_death));
	}
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
