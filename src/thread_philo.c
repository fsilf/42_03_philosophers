/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:43:15 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 22:02:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

static int	check_death(t_philo_args *philo_args)
{
		pthread_mutex_lock(&(philo_args->args->mutex_end));
		if (philo_args->args->end == 1)
			return (1);
		pthread_mutex_unlock(&(philo_args->args->mutex_end));
		return (0);
}

static int	philo_step(t_philo_args *philo_args, \
						t_queue_args *queue_args, char type)
{
	ssize_t	time_to;
	struct timeval	log_time;
	long unsigned	ms_time;
	pthread_t		phtread_sleep_id;

	if (check_death(philo_args))
		return (NULL);
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
	queue_args->log = log_new(ms, type, queue_args->philo);
	send_log(queue_args, 'y');
	pthread_join(phtread_sleep_id, NULL);
	return (0);
}

static int	assign_forks(t_philo_args *philo_args, t_queue_args *queue_args, \
							ssize_t *fork1, ssize_t *fork2)
{
	ssize_t	temp;

	if (queue_args->philo != 0)
		*fork1 = queue_args->philo - 1;
	else
		*fork1 = philo_args->num_philo - 1;
	*fork2 = queue_args->philo;
	if (queue_args->philo == philo_args->num_philos - 1)
	{
		temp = *fork1;
		*fork1 = *fork2;
		*fork2 = temp;
	}
	return (0);
}

static int	take_forks(t_philo_args *philo_args, ssize_t fork1, ssize_t fork2)
{
	while (1)
	{
		if (philo_args->mutex[fork1] == 0 && philo_args->mutex[fork2] == 0)
		{
			pthread_mutex_lock(&(philo_args->mutex[fork1]));
			pthread_mutex_lock(&(philo_args->mutex[fork2]));
			philo_args->forks[fork1] = 1;
			philo_args->forks[fork2] = 1;
			break ;
		}
		else
			usleep(500);//00! probar otros valores?
	}
	return (0);
}

static int	release_forks(t_philo_args *philo_args, \ 
							ssize_t fork1, ssize_t fork2)
{
	philo_args->forks[fork1] = 0;
	pthread_mutex_unlock(&(philo_args->mutex[fork1]));
	philo_args->forks[fork2] = 0;
	pthread_mutex_unlock(&(philo_args->mutex[fork2]));
	return (0);
}

void	*thread_philo(void *arg)
{
	t_philo_args	*philo_args;
	t_queue_args	queue_args;
	ssize_t	fork1;
	ssize_t	fork2;

	assign_forks(philo_args, queue_args, &fork1, &fork2);
	pthread_mutex_lock(philo_args->mutex_philo);
	philo_args = arg;
	queue_args.philo = philo_args->philo;
	pthread_mutex_unlock(philo_args->mutex_philo);
	queue_args.head_log = philo_args->queue_args->head_log;
	queue_args.mutex = philo_args->queue_args->mutext;
	while (1)
	{
		if (check_death(philo_args))
			return (NULL);
		take_forks(philo_args, fork1, fork2);
		philo_step(philo_args, &queue_args, 'e');
		if (check_death(philo_args))
			return (NULL);
		release_forks(philo_args, &queue_args, fork1, fork2);
		philo_step(philo_args, &queue_args, 's');
		philo_step(philo_args, &queue_args, 't');
	}
	return (NULL);
}
