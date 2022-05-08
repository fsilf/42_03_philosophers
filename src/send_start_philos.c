/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:26:48 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 20:23:47 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "philo.h"

static int	assign_forks(t_philo_args *philo)
{
	if (philo->philo % 2 == 0)
	{
		philo->fork1 = philo->philo;
		philo->fork2 = (philo->philo + 1) % philo->args->num_philo;
	}
	else
	{
		philo->fork1 = (philo->philo + 1) % philo->args->num_philo;
		philo->fork2 = philo->philo;
	}
	printf("philo:%zd has fork1:%zd, fork2:%zd\n", \
			philo->philo, philo->fork1, philo->fork2);
	return (0);
}

int	set_philo_args(t_args *args, t_philo_args *philo)
{
	ft_memset(philo, 0, sizeof (t_philo_args));
	philo->philo = args->philo;
	philo->args = args;
	return (0);
}

int	start_simulation_sync(t_args *args, t_philo_args *philo)
{
	if (philo->philo == args->num_philo - 1)
	{
		if (pthread_mutex_destroy(&(args->mutex_philo)))
		{
			perror("thread_philo: mutex_destroy mutex_philo");
			return (1);
		}
		pthread_mutex_unlock(&args->mutex_start);
		gettimeofday(&(args->tv_init), NULL);
		test_print_timeval(args->tv_init);
	}
	else
	{
		pthread_mutex_lock(&args->mutex_start);
		pthread_mutex_unlock(&args->mutex_start);
	}
	add_ms(args->tv_init, args->time_life, &(philo->life));
	return (0);
}

static void	*thread_philo(void *arg)
{
	t_args			*args;
	t_philo_args	philo;

	args = arg;
	set_philo_args(args, &philo);
	assign_forks(&philo);
	pthread_mutex_unlock(&(args->mutex_philo));
	if (start_simulation_sync(args, &philo))
		return (NULL);
	if (send_check_lives(&philo))
		return (NULL);
	while (1)
	{
		if (philo.args->end == 1)
			break ;
		/*
		if (take_forks(philo_args, &queue_args, fork1, fork2))
			return (NULL);
		if (philo_step(philo_args, &queue_args, 'e'))
			return (NULL);
		release_forks(philo_args, fork1, fork2);
		if (philo_step(philo_args, &queue_args, 's'))
			return (NULL);
		if (philo_step(philo_args, &queue_args, 't'))
			return (NULL);
		*/
		usleep(1000);
	}
	if (pthread_join(philo.lives_id, NULL))
	{
		perror("send_check_lives: pthread_join:");
		return (NULL);
	}
	return (NULL);
}

int	send_start_philos(t_args *args, t_id_store *pthread_ids)
{
	ssize_t			i;

	i = 0;
	pthread_mutex_lock(&(args->mutex_start));
	while (i < args->num_philo)
	{
		pthread_mutex_lock(&(args->mutex_philo));
		args->philo = i;
		if (pthread_create(&(pthread_ids->philo_ids[i]), NULL, \
							&thread_philo, args))
		{
			perror("send_start_philos: pthread_create");
			return (1);
		}
		i++;
	}
	return (0);
}
