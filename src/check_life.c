/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:51:47 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 19:06:37 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> //remove
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

int	check_lives(t_args **args, long unsigned *philo_lives, \
					t_queue_args *queue_args)
{
	ssize_t			i;
	long unsigned	ms_time;
	t_queue_args	*local_queue;

	while (1)
	{
		i = 0;
		while (i < (*args)->num_philo)
		{
			get_curr_time_ms(&ms_time);
			if (ms_time > philo_lives[i])
			{
				/*
				printf("ms_time: %ld, philo_lives[%zd]:%ld\n", \
						ms_time, i, philo_lives[i]);
				exit(0);
				*/
				queue_args->philo = i;
				(*args)->end = 1;
				set_local_queue_args(queue_args, &local_queue, ms_time, 'd');
				if (send_log(local_queue, 'n'))
					return (1);
				return (0);
			}
			i++;
		}
		usleep(1000);
	}
}

int	send_check_lives(t_philo_args *philo_args, \
						t_queue_args *queue_args, t_id_store *pthread_ids)
{
	t_check_life	lives_args;

	lives_args.args = &(philo_args->args);
	lives_args.philo_lives = philo_args->philo_lives;
	lives_args.queue_args = queue_args;
	if (pthread_create(&(pthread_ids->lives_id), NULL, &thread_lives, \
									&lives_args))
	{
		perror("send_check_lives: pthread_create:");
		return (1);
	}
	return (0);
}
