/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:25:06 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 18:07:35 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

static int	send_usleep(ssize_t *time_to, pthread_t *pthread_sleep_id)
{
	if (pthread_create(pthread_sleep_id, NULL, &thread_usleep, (void *)time_to))
	{
		perror("send_usleep: pthread_create");
		return (1);
	}
	return (0);
}

int	philo_step(t_philo_args *philo_args, \
						t_queue_args *queue_args, char type)
{
	ssize_t			time_to;
	struct timeval	log_time;
	long unsigned	ms_time;
	pthread_t		pthread_sleep_id;
	t_queue_args	*local_queue;

	gettimeofday(&log_time, NULL);
	time_to = 0;
	if (type == 'e')
		time_to = philo_args->args->time_eating;
	else if (type == 's')
		time_to = philo_args->args->time_unhungry;
	else if (type == 't')
		time_to = philo_args->args->time_think;
	if (send_usleep(&time_to, &pthread_sleep_id))
		return (1); //gestionar exits
	ms_time = convert_to_milisecs(&log_time);
	if (type == 'e')
	{
		philo_args->philo_lives[queue_args->philo] = ms_time + \
											philo_args->args->time_life;
	}
	set_local_queue_args(queue_args, &local_queue, ms_time, type);
	send_log(local_queue, 'y');
	pthread_join(pthread_sleep_id, NULL);
	return (0);
}
