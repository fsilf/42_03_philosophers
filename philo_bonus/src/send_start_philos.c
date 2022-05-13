/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:22:45 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 03:22:49 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static int	set_philo_args(t_args *args, t_philo_args *philo)
{
	char	name[4];

	name[0] = 'c';
	name[1] = 'o';
	name[3] = '\0';
	ft_memset(philo, 0, sizeof (t_philo_args));
	philo->philo = args->philo;
	name[2] = philo->philo + 48;
	philo->args = args;
	philo->args->sem_death = sem_open("death", O_RDWR);
	philo->args->sem_philo = sem_open("philo", O_RDWR);
	philo->args->forks = sem_open("forks", O_RDWR);
	philo->args->sem_print = sem_open("print", O_RDWR);
	philo->args->sem_start = sem_open("start", O_RDWR);
	philo->life = args->mu_init + (args->time_life * 1000);
	philo->sem_counter = sem_open(name, O_RDWR);
	//printf("seated:%zd\n", args->seated);
	//printf("philo->life: %ld\n", philo->life);
	return (0);
}

static int	start_simulation_sync(t_args *args)
{
	if (args->seated == args->num_philo - 1)
	{
		sem_post(args->sem_start);
	}
	else
	{
		sem_wait(args->sem_start);
		sem_post(args->sem_start);
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
	printf("heeeellooooo, philo:%zd\n", philo.philo);
	if (pthread_join(philo.lives_id, NULL))
	{
		perror("run_philo: pthread_join lives_id");
		return (1);
	}
	if (pthread_join(philo.get_time_id, NULL))
	{
		perror("run_philo: pthread_join lives_id");
		return (1);
	}
	return (0);
}

int	send_start_philos(t_args *args, t_id_store *pids)
{
	ssize_t			i;

	i = 0;
	gettimeofday(&(args->tv_init), NULL);
	args->mu_init = convert_to_microsecs(args->tv_init);
	sem_wait(args->sem_start);
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
			printf("exits ok\n");
			exit(EXIT_SUCCESS);
		}
		args->seated = args->seated + 1;
		usleep(1000);
		i++;
	}
	return (0);
}
