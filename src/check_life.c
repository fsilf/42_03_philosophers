/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:51:47 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/03 21:52:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

static int	send_log(t_queue_args *queue_args)
{
	pthread_t	thread_add_id;

	if (pthread_create(&thread_add_id, NULL, &thread_log_add, &queue_args))
	{
		perror("pthread_create log_add");
		return (1);
	}
	if (pthread_detach(thread_add_id))
	{
		perror("pthread_detach log_add");
		return (1);
	}
	return (0);
}

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
				queue_args.log = log_new(ms_time, 'd', i);
				if (send_log(queue_args))
					return (1);
				//gestionar exits
				return (0);
			}
			i++;
		}
		usleep(2000);
	}
}

int	send_check_lives(t_args *args, ssize_t *philo_lives, t_queue_args *queue_args)
{
	pthread_t	pthread_lives_id;

}
