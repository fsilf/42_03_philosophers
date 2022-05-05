/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:51:47 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 13:42:33 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

static int	get_curr_time_ms(long unsigned *ms_time)
{
	struct timeval	log_time;

	ft_memset(&log_time, 0, sizeof (struct timeval));
	gettimeofday(&log_time, NULL);
	*ms_time = 0;
	*ms_time = convert_to_milisecs(&log_time);
	return (0);
}

int	check_lives(t_args *args, long unsigned *philo_lives, \
					t_queue_args *queue_args)
{
	ssize_t			i;
	long unsigned	ms_time;
	t_queue_args	*local_queue;

	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			get_curr_time_ms(&ms_time);
			if (ms_time > philo_lives[i])
			{
				pthread_mutex_lock(&(args->mutex_end));
				args->end = 1;
				pthread_mutex_unlock(&(args->mutex_end));
				set_local_queue_args(queue_args, &local_queue, ms_time, 'd');
				if (send_log(local_queue, 'n'))
					return (1);
				return (0);
			}
			i++;
		}
		usleep(500);
	}
}

int	send_check_lives(t_args *args, long unsigned *philo_lives, \
						t_queue_args *queue_args)
{
	pthread_t		pthread_lives_id;
	t_check_life	lives_args;

	lives_args.args = args;
	lives_args.philo_lives = philo_lives;
	lives_args.queue_args = queue_args;
	if (pthread_create(&pthread_lives_id, NULL, &thread_lives, \
									&lives_args))
	{
		perror("send_check_lives: pthread_create:");
		return (1);
	}
	if (pthread_join(pthread_lives_id, NULL))
	{
		perror("send_check_live: thread_join");
		return (1);
	}
	return (0);
}
