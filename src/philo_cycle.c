/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:03:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/09 14:08:02 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static int	release_forks(t_philo_args *philo)
{
	philo->args->forks[philo->fork1] = 0;
	pthread_mutex_unlock(&(philo->args->mutex_fork[philo->fork1]));
	philo->args->forks[philo->fork2] = 0;
	pthread_mutex_unlock(&(philo->args->mutex_fork[philo->fork2]));
	gettimeofday(&(philo->tv_begin), NULL);
	add_ms(philo->tv_begin, philo->args->time_sleep, &(philo->tv_end));
	return (0);
}

static int	take_forks(t_philo_args *philo)
{
	pthread_mutex_lock(&(philo->args->mutex_fork[philo->fork1]));
	if (philo->args->forks[philo->fork1] == 0)
	{
		philo->args->forks[philo->fork1] = 1;
		gettimeofday(&(philo->tv_fork1), NULL);
		pthread_mutex_lock(&(philo->args->mutex_fork[philo->fork2]));
		if (philo->args->forks[philo->fork2] == 0)
		{
			philo->args->forks[philo->fork2] = 1;
			gettimeofday(&(philo->tv_fork2), NULL);
		}
		else
			return (1);
	}
	else
		return (1);
	gettimeofday(&(philo->tv_begin), NULL);
	add_ms(philo->tv_begin, philo->args->time_eat, &(philo->tv_end));
	pthread_mutex_lock(&(philo->args->mutex_death));
	add_ms(philo->tv_begin, philo->args->time_life, &(philo->life));
	pthread_mutex_unlock(&(philo->args->mutex_death));
	return (0);
}

int	philo_cycle(t_philo_args *philo)
{
	while (1)
	{
		if (take_forks(philo))
		{
			write(2, "philo_cycle: take_forks error", 29);
			return (1);
		}
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
		{
			release_forks(philo);
			return (1);
		}
		printf("sec:%ld, usec:%ld, philo:%zd has taken a fork\n", \
				philo->tv_fork1.tv_sec, philo->tv_fork1.tv_usec, \
				philo->philo);
		printf("sec:%ld, usec:%ld, philo:%zd has taken a fork\n", \
				philo->tv_fork2.tv_sec, philo->tv_fork2.tv_usec, \
				philo->philo);
		printf("sec:%ld, usec:%ld, philo:%zd is eating\n", \
				philo->tv_begin.tv_sec, philo->tv_begin.tv_usec, \
				philo->philo);
		printf("sec:%ld, usec:%ld, philo:%zd philo->life\n", \
				philo->life.tv_sec, philo->life.tv_usec, \
				philo->philo);
		printf("sec:%ld, usec:%ld, philo:%zd philo->tv_end\n", \
				philo->tv_end.tv_sec, philo->tv_end.tv_usec, \
				philo->philo);
		custom_sleep(philo->tv_end);
		release_forks(philo);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
			return (1);
		printf("sec:%ld, usec:%ld, philo:%zd is sleeping\n", \
				philo->tv_begin.tv_sec, philo->tv_begin.tv_usec, \
				philo->philo);
		custom_sleep(philo->tv_end);
		gettimeofday(&(philo->tv_begin), NULL);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
			return (1);
		printf("sec:%ld, usec:%ld, philo:%zd is thinking\n", \
				philo->tv_begin.tv_sec, philo->tv_begin.tv_usec, \
				philo->philo);
		usleep(50);
		/*
		if (philo_step(philo_args, &queue_args, 's'))
			return (NULL);
		if (philo_step(philo_args, &queue_args, 't'))
			return (NULL);
		*/
	}
	return (0);
}
