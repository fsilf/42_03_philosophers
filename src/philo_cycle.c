/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:03:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/09 22:03:27 by fsilva-f         ###   ########.fr       */
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

static int	take_fork2(t_philo_args *philo)
{
	pthread_mutex_lock(&(philo->args->mutex_fork[philo->fork2]));
	if (philo->args->forks[philo->fork2] == 0)
	{
		philo->args->forks[philo->fork2] = 1;
		gettimeofday(&(philo->tv_fork2), NULL);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
		{
			release_forks(philo);
			return (0);
		}
		print_msg(philo, 'f', philo->tv_fork2);
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
		gettimeofday(&(philo->tv_fork1), NULL);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
		{
			pthread_mutex_unlock(&(philo->args->mutex_fork[philo->fork1]));
			return (0);
		}
		print_msg(philo, 'f', philo->tv_fork1);
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
	if (check_death(philo->args->end, &(philo->args->mutex_death)))
	{
		release_forks(philo);
		return (0);
	}
	print_msg(philo, 'e', philo->tv_begin);
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
		custom_sleep(philo->tv_end, philo->args->num_philo);
		release_forks(philo);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
			return (1);
		print_msg(philo, 's', philo->tv_begin);
		custom_sleep(philo->tv_end, philo->args->num_philo);
		gettimeofday(&(philo->tv_begin), NULL);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
			return (1);
		print_msg(philo, 't', philo->tv_begin);
		//usleep(1 * philo->args->num_philo);
		usleep(100);
	}
	return (0);
}
