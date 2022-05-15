/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 17:34:04 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static void	*thread_lives(void *arg)
{
	t_philo_args	*philo;

	philo = (t_philo_args *)arg;
	while (philo->life == 0)
		usleep(50);
	while (1)
	{
		if (philo->args->end == 1)
			return (NULL);
		if (sem_wait(philo->args->sem_death))
			write(2, "thread_lives: sem_wait sem_death\n", 33);
		if (philo->args->mu_since > philo->life)
		{
			print_msg(philo, 'd');
			philo->args->end = 1;
			sem_post(philo->args->sem_death);
			exit(EXIT_SUCCESS);
			return (NULL);
		}
		sem_post(philo->args->sem_death);
		usleep(800);
	}
	return (NULL);
}

int	send_check_lives(t_philo_args *philo)
{
	if (pthread_create(&(philo->lives_id), NULL, &thread_lives, (void *)philo))
	{
		write(2, "send_check_lives: pthread_create:\n", 35);
		return (1);
	}
	return (0);
}
