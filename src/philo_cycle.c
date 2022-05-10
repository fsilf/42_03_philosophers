/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:03:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/10 14:30:55 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static int	release_forks_and_set_sleep(t_philo_args *philo)
{
	philo->args->forks[philo->fork1] = 0;
	pthread_mutex_unlock(&(philo->args->mutex_fork[philo->fork1]));
	philo->args->forks[philo->fork2] = 0;
	pthread_mutex_unlock(&(philo->args->mutex_fork[philo->fork2]));
	gettimeofday(&(philo->tv_begin), NULL);
	print_msg(philo, 's');
	add_ms(philo->tv_begin, philo->args->time_sleep, &(philo->tv_end));
	return (0);
}

static int	take_fork2(t_philo_args *philo)
{
	pthread_mutex_lock(&(philo->args->mutex_fork[philo->fork2]));
	if (philo->args->forks[philo->fork2] == 0)
	{
		philo->args->forks[philo->fork2] = 1;
		if (print_msg(philo, 'f'))
		{
			release_forks_and_set_sleep(philo);
			return (0);
		}
	}
	else
		return (1);
	return (2);
}

static int	take_fork1(t_philo_args *philo)
{
	int	res;

	pthread_mutex_lock(&(philo->args->mutex_fork[philo->fork1]));
	if (philo->args->forks[philo->fork1] == 0)
	{
		philo->args->forks[philo->fork1] = 1;
		if (print_msg(philo, 'f'))
		{
			pthread_mutex_unlock(&(philo->args->mutex_fork[philo->fork1]));
			return (0);
		}
		res = take_fork2(philo);
		if (res != 2)
			return (res);
	}
	else
		return (1);
	return (2);
}

static int	take_forks(t_philo_args *philo)
{
	int	res;

	res = take_fork1(philo);
	if (res != 2)
		return (res);
	gettimeofday(&(philo->tv_begin), NULL);
	add_ms(philo->tv_begin, philo->args->time_eat, &(philo->tv_end));
	pthread_mutex_lock(&(philo->args->mutex_death));
	add_ms(philo->tv_begin, philo->args->time_life, &(philo->life));
	pthread_mutex_unlock(&(philo->args->mutex_death));
	if (print_msg(philo, 'e'))
	{
		release_forks_and_set_sleep(philo);
		return (0);
	}
		
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
		custom_sleep(philo->tv_end);
		if (release_forks_and_set_sleep(philo))
			return (1);
		custom_sleep(philo->tv_end);
		if (print_msg(philo, 't'))
			return (1);
		//usleep(1 * philo->args->num_philo);
		usleep(101);
	}
	return (0);
}
