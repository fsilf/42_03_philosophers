/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:26:48 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/11 20:10:39 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "philo.h"

static int	assign_forks(t_philo_args *philo)
{
	if (philo->args->num_philo == 1)
	{
		gettimeofday(&(philo->args->tv_init), NULL);
		printf("0 0 has taken a fork\n");
		printf("%zd 0 died\n", philo->args->time_life + 1);
		return (1);
	}
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
	return (0);
}

int	set_philo_args(t_args *args, t_philo_args *philo)
{
	ft_memset(philo, 0, sizeof (t_philo_args));
	philo->philo = args->philo;
	args->seated = args->seated + 1;
	philo->args = args;
	return (0);
}

static int	start_simulation_sync(t_args *args, t_philo_args *philo)
{
	if (args->seated == args->num_philo - 1)
	{
		pthread_mutex_lock(&(args->mutex_death));
		gettimeofday(&(args->tv_init), NULL);
		test_print_timeval(args->tv_init);
		args->mu_init = convert_to_microsecs(args->tv_init);
		pthread_mutex_unlock(&(args->mutex_death));
		args->start = 1;
		philo->life = args->mu_init + (args->time_life * 1000);
	}
	else
	{
		while (1)
		{
			if (args->start == 1)
			{
				philo->life = args->mu_init + (args->time_life * 1000);
				break ;
			}
			usleep(50);
		}
	}
	return (0);
}

static void	*thread_philo(void *arg)
{
	t_args			*args;
	t_philo_args	philo;

	args = arg;
	set_philo_args(args, &philo);
	if (assign_forks(&philo))
		return (NULL);
	pthread_mutex_unlock(&(args->mutex_philo));
	if (start_simulation_sync(args, &philo))
		return (NULL);
	if (send_check_lives(&philo))
		return (NULL);
	usleep(1000);
	if (philo.philo % 2 == 0)
		custom_sleep(&philo, args->time_eat);
	philo_cycle(&philo);
	if (pthread_join(philo.lives_id, NULL))
	{
		perror("thread_philo: pthread_join lives_id");
		return (NULL);
	}
	return (NULL);
}

int	send_start_philos(t_args *args, t_id_store *pthread_ids)
{
	ssize_t			i;

	i = 0;
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
		usleep(1000);
		i++;
	}
	return (0);
}
