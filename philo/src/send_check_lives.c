/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 17:17:50 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*thread_lives(void *arg)
{
	t_philo_args	*philo;

	philo = (t_philo_args *)arg;
	while (philo->life == 0)
		usleep(50);
	while (1)
	{
		if (pthread_mutex_lock(&(philo->args->mutex_death)))
			write(2, "thread_lives: mutex_lock mutex_death\n", 37);
		if (philo->args->end == 1)
		{
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		if (philo->args->mu_since > philo->life)
		{
			print_msg(philo, 'd');
			philo->args->end = 1;
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->args->mutex_death));
		usleep(800);
	}
	return (NULL);
}

int	send_check_lives(t_philo_args *philo)
{
	if (pthread_create(&(philo->lives_id), NULL, &thread_lives, (void *)philo))
	{
		write(2, "send_check_lives: pthread_create\n", 33);
		return (1);
	}
	return (0);
}
