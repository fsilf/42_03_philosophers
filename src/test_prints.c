/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:12:04 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 19:33:24 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

void	test_print_args(t_args *args)
{
	printf("num_philo:%zd\n", args->num_philo);
	printf("time_life:%zd\n", args->time_life);
	printf("time_eating:%zd\n", args->time_eating);
	printf("time_unhungry:%zd\n", args->time_unhungry);
	printf("time_think:%zd\n", args->time_think);
	printf("num_loops:%zd\n", args->num_loops);
	printf("init_time ms_init:%ld\n", args->ms_init);
}

void	test_print_timeval(struct timeval *tv)
{
	printf("secs:%d, usecs:%d\n", \
			(unsigned int)tv->tv_sec, (unsigned int)tv->tv_usec);
}

void	test_print_philo_lives(t_args *args, long unsigned *philo_lives)
{
	ssize_t	i;

	i = 0;
	printf("philo_lives:\n");
	while (i < args->num_philo)
	{
		printf("philo_lives[%zd]:%ld\n", i, philo_lives[i]);
		i++;
	}
}

void	test_print_queue_args(t_queue_args *queue_args)
{
	printf("queue_args:\n");
	if (queue_args->head_log != NULL && *(queue_args->head_log)	== NULL)
		printf("*(queue_args->head_log) == NULL\n");
	if (queue_args->log == NULL)
		printf("queue_args->log == NULL\n");
	printf("queue_args->philo: %zd\n", queue_args->philo);
	pthread_mutex_lock(queue_args->mutex);
	printf("queue_mutex ON\n");
	pthread_mutex_unlock(queue_args->mutex);
	printf("queue_mutex OFF\n");
}
