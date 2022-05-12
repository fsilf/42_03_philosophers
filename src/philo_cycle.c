/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:03:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 10:53:01 by fsilva-f         ###   ########.fr       */
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
	if (print_msg(philo, 's'))
		return (1);
	return (0);
}

static int	take_fork2(t_philo_args *philo)
{
	pthread_mutex_lock(&(philo->args->mutex_fork[philo->fork2]));
	if (philo->args->forks[philo->fork2] == 0)
		philo->args->forks[philo->fork2] = 1;
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
	pthread_mutex_lock(&(philo->args->mutex_death));
	philo->mu_start_action = philo->args->mu_since;
	pthread_mutex_unlock(&(philo->args->mutex_death));
	if (philo->mu_start_action != 0)
		philo->life = philo->mu_start_action + (philo->args->time_life * 1000);
	else
		return (0);
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
		if (custom_sleep(philo, philo->args->time_eat))
		{
			release_forks_and_set_sleep(philo);
			return (0);
		}
		if (release_forks_and_set_sleep(philo))
			return (0);
		if (custom_sleep(philo, philo->args->time_sleep))
			return (0);
		if (print_msg(philo, 't'))
			return (1);
		usleep(200);
	}
	return (0);
}
