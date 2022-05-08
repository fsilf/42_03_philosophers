/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:03:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/09 00:06:17 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "philo.h"

int	philo_cycle(t_philo_args *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->args->mutex_death);
		if (check_death(philo->args->end, &(philo->args->mutex_death)))
			break ;
		pthread_mutex_unlock(&philo->args->mutex_death);
		/*
		if (take_forks(philo))
			return (NULL);
		if (philo_step(philo_args, &queue_args, 'e'))
			return (NULL);
		release_forks(philo_args, fork1, fork2);
		if (philo_step(philo_args, &queue_args, 's'))
			return (NULL);
		if (philo_step(philo_args, &queue_args, 't'))
			return (NULL);
		*/
		usleep(1000);//remove (for testing empty) 
	}
	return (0);
}
