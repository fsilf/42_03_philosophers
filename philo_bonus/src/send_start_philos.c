/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:22:45 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 14:02:30 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static int	start_simulation_sync(t_args *args)
{
	if (args->seated == args->num_philo - 1)
		sem_post(args->sem_start);
	else
	{
		sem_wait(args->sem_start);
		sem_post(args->sem_start);
	}
	return (0);
}

static int	wait_for_pthreads(pthread_t lives_id, pthread_t get_time_id)
{
	if (pthread_join(lives_id, NULL))
	{
		perror("run_philo: pthread_join lives_id");
		return (1);
	}
	if (pthread_join(get_time_id, NULL))
	{
		perror("run_philo: pthread_join lives_id");
		return (1);
	}
	return (0);
}

static int	run_philo(t_args *args)
{
	t_philo_args	philo;

	set_philo_args(args, &philo);
	sem_post(args->sem_philo);
	if (send_get_time(args, &(philo.get_time_id)))
		return (1);
	if (start_simulation_sync(args))
		return (1);
	if (send_check_lives(&philo))
		return (1);
	sem_post(philo.args->forks);
	usleep(100);
	if (philo.philo % 2 == 1)
		custom_sleep(&philo, args->time_eat);
	philo_cycle(&philo);
	if (wait_for_pthreads(philo.lives_id, philo.get_time_id))
		return (1);
	return (0);
}

static int	start_philos_loop(t_args *args, t_id_store *pids)
{
	ssize_t			i;

	i = 0;
	while (i < args->num_philo)
	{
		sem_wait(args->sem_philo);
		args->philo = i;
		pids->philo_ids[i] = fork();
		if (pids->philo_ids[i] == -1)
		{
			perror("send_start_philos: fork");
			return (1);
		}
		else if (pids->philo_ids[i] == 0)
		{
			if (run_philo(args))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		args->seated = args->seated + 1;
		usleep(1000);
		i++;
	}
	return (0);
}

int	send_start_philos(t_args *args, t_id_store *pids)
{
	gettimeofday(&(args->tv_init), NULL);
	args->mu_init = convert_to_microsecs(args->tv_init);
	sem_wait(args->sem_start);
	if (start_philos_loop(args, pids))
		return (1);
	return (0);
}
