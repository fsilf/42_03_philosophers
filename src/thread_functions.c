/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:24:32 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 15:17:49 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

void	*thread_print_queue(void *arg)
{
	t_queue_args	*queue_args;
	char			*res;

	queue_args = arg;
	res = NULL;
	//res = ft_strdup("nope");
	if (log_print_loop(queue_args->head_log, queue_args->mutex))
	{
		write(2, "log_print_loop error\n", 22);
		res = ft_strdup("error");
	}
	return (res);
}

void	*thread_log_add(void *arg)
{
	t_queue_args	*queue_args;

	queue_args = arg;
	log_addback(queue_args->head_log, queue_args->log, queue_args->mutex);
	return (NULL);
}

void	*thread_usleep(void *arg)
{
	ssize_t	time_to;

	time_to = (ssize_t)arg;
	usleep(time_to);
	return (NULL);
}

static int	philo_step(t_philo_args *philo_args, \
						t_queue_args queue_args, char type)
{
	ssize_t	time_to;
	struct timeval	log_time;
	long unsigned	ms_time;
	pthread_t		phtread_sleep_id;

	gettimeofday(&log_time, NULL);
	time_to = 0;
	if (type == 'e')
		time_to = philo_args->time_eating;
	else if (type == 's')
		time_to = philo_args->time_unhungry;
	else if (type == 't')
		time_to = philo_args->time_think;
	pthread_sleep_id = send_usleep(time_to);
	if (pthread_sleep_id < 0)
		return (1);// gestionar exits
	if (type == 'e')
		reset_life(philo_args->philo_lives, philo_args->philo, ms_time);
	ms_time = convert_to_milisecs(&log_time);
	queue_args.log = log_new(ms, type, philo_args->philo);
	send_log(queue_args, 'y');
	pthread_join(phtread_sleep_id, NULL);
	return (0);
}

void	*thread_philo(void *arg)
{
	t_philo_args	*philo_args;
	t_queue_args	queue_args;

	philo_args = arg;
	queue_args.head_log = philo_args->queue_args->head_log;
	queue_args.mutex = philo_args->queue_args->mutext;
	while (1)
	{
		take_forks(philo_args);//00! write function
		philo_step(philo_args, queue_args, 'e');
		release_forks(philo_args);//00! write function
		philo_step(philo_args, queue_args, 's');
		philo_step(philo_args, queue_args, 't');
	}
	return (NULL);
}

void	*thread_lives(void *arg)
{
	t_check_life	*lives_args;

	lives_args = arg;
	check_lives(lives_args->args, lives_args->philo_lives);
	return (NULL);
}
