/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:03:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 03:38:03 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_bonus.h"

static int	release_forks_and_set_sleep(t_philo_args *philo)
{
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
	if (add_num_loops(philo))
		return (1);
	if (print_msg(philo, 's'))
		return (1);
	return (0);
}

static int	take_forks(t_philo_args *philo)
{
	sem_wait(philo->args->forks);
	if (print_msg(philo, 'f'))
	{
		sem_post(philo->args->forks);
		return (0);
	}
	sem_wait(philo->args->forks);
	sem_wait(philo->args->sem_death);
	philo->mu_start_action = philo->args->mu_since;
	sem_post(philo->args->sem_death);
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
	philo->args->mu_init = philo->args->mu_init + \
									(philo->args->num_philo * 1150);
	philo->life = philo->args->mu_init + (philo->args->time_life * 1000);
	usleep(800);
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
		if (philo->args->num_philo < 10)
			usleep(1000);
	}
	return (0);
}
