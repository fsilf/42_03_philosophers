/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 20:33:13 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

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
		if (philo->args->end == 1)
			return (NULL);
		gettimeofday(&curr_time, NULL);
		if (compare_timevals(philo->life, curr_time))
		{
			philo->args->end = 1;
			printf("philo %zd died\n", philo->philo);
			return (NULL);
		}
		usleep(1000);
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
