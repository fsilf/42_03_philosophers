/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:51:47 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 19:30:54 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

int	check_lives(t_args *args, ssize_t *philo_lives, t_queue_args *queue_args)
{
	ssize_t			i;
	struct timeval	log_time;
	long unsigned	ms_time;

	log = NULL;
	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			ft_memset(&log_time, 0, sizeof (struct timeval));
			getttimeofday(&log_time, NULL);
			ms_time = 0;
			ms_time = ms_convert_to_milisecs(&log_time);
			if (ms_time > philo_lives[i])
			{
				pthread_mutex_lock(&(args->mutex_end));
				args->end = 1;
				pthread_mutex_unlock(&(args->mutex_end));
				queue_args.log = log_new(ms_time, 'd', i);
				if (send_log(queue_args, 'n'))
					return (1);
				return (0);
			}
			i++;
		}
		usleep(500);
	}
}

pthread_t	send_check_lives(t_args *args, ssize_t *philo_lives, \
						t_queue_args *queue_args)
{
	pthread_t		pthread_lives_id;
	t_check_life	lives_args;

	thread_res = -1;
	lives_args.args = args;
	lives_args.philo_lives = philo_lives;
	lives_args.queue_args = queue_args;
	if (pthread_create(pthread_lives_id, NULL, &thread_lives, \
									lives_args))
	{
		perror("send_check_lives: pthread_create:");
		return (1);
	}
	if (pthread_join(pthread_lives_id))
	{
		perror("send_check_live: thread_join");
		return (1);
	}
	return (0);
}
