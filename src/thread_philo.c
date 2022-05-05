/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:43:15 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 21:09:55 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h> //test, remove
#include <sys/time.h>
#include "philo.h"

static int	assign_forks(t_philo_args *philo_args, t_queue_args *queue_args, \
							ssize_t *fork1, ssize_t *fork2)
{
	ssize_t	temp;

	if (queue_args->philo != 0)
		*fork1 = queue_args->philo - 1;
	else
		*fork1 = philo_args->args->num_philo - 1;
	*fork2 = queue_args->philo;
	if (queue_args->philo == philo_args->args->num_philo - 1)
	{
		temp = *fork1;
		*fork1 = *fork2;
		*fork2 = temp;
	}
	return (0);
}

static int	log_fork(t_queue_args *queue_args)
{
	t_queue_args	*local_queue;
	struct timeval	log_time;
	long unsigned	ms_time;

	gettimeofday(&log_time, NULL);
	ms_time = convert_to_milisecs(&log_time);
	if (set_local_queue_args(queue_args, &local_queue, ms_time, 'f'))
		return (1);//gestionar exits
	send_log(local_queue, 'y');
	return (0);
}

static int	take_forks(t_philo_args *philo_args, t_queue_args *queue_args, \
						ssize_t fork1, ssize_t fork2)
{
	while (1)
	{
		if (philo_args->forks[fork1] == 0 && \
			philo_args->forks[fork2] == 0)
		{
			pthread_mutex_lock(&(philo_args->mutex_fork[fork1]));
			pthread_mutex_lock(&(philo_args->mutex_fork[fork2]));
			philo_args->forks[fork1] = 1;
			if (log_fork(queue_args))
				return (1);
			philo_args->forks[fork2] = 1;
			if (log_fork(queue_args))
				return (1);
			break ;
		}
		else
			usleep(500);
		//00! probar otros valores? variar con num_philos?
	}
	return (0);
}

static int	release_forks(t_philo_args *philo_args, \
							ssize_t fork1, ssize_t fork2)
{
	philo_args->forks[fork1] = 0;
	pthread_mutex_unlock(&(philo_args->mutex_fork[fork1]));
	philo_args->forks[fork2] = 0;
	pthread_mutex_unlock(&(philo_args->mutex_fork[fork2]));
	return (0);
}

void	*thread_philo(void *arg)
{
	t_philo_args	*philo_args;
	t_queue_args	queue_args;
	ssize_t			fork1;
	ssize_t			fork2;

	philo_args = arg;
	queue_args.philo = philo_args->philo;
	pthread_mutex_unlock(philo_args->mutex_philo);
	queue_args.head_log = philo_args->head_log;
	queue_args.mutex = philo_args->mutex_queue;
	test_print_queue_args(&queue_args);
	assign_forks(philo_args, &queue_args, &fork1, &fork2);
	while (1)
	{
		if (check_death(philo_args))
			return (NULL);
		if (take_forks(philo_args, &queue_args, fork1, fork2))
			return (NULL);
		philo_step(philo_args, &queue_args, 'e');
		if (check_death(philo_args))
			return (NULL);
		release_forks(philo_args, fork1, fork2);
		philo_step(philo_args, &queue_args, 's');
		philo_step(philo_args, &queue_args, 't');
	}
	return (NULL);
}
