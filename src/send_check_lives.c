/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_check_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/11 20:09:01 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

int	check_death(ssize_t end, pthread_mutex_t *mutex_death)
{
	pthread_mutex_lock(mutex_death);
	if (end == 1)
	{
		pthread_mutex_unlock(mutex_death);
		return (1);
	}
	pthread_mutex_unlock(mutex_death);
	return (0);
}
/*
static int	check_loop(t_philo_args *philo, struct timeval *curr_time)
{
	if (pthread_mutex_lock(&(philo->args->mutex_death)))
		perror("thread_lives: mutex_lock mutex_death");
	if (philo->args->end == 1)
	{
		pthread_mutex_unlock(&(philo->args->mutex_death));
		return (1);
	}
	if (philo->args->mu_since > philo->mu_life)
	{
		print_msg(philo, 'd'); //00! antes o despues de setear end = 1?
		philo->args->end = 1;
		pthread_mutex_unlock(&(philo->args->mutex_death));
		philo->args->mu_since = 0;//esta bien reseteando a 0?
		return (1);
	}
	pthread_mutex_unlock(&(philo->args->mutex_death));
	usleep(200);// coordinar con get_time usleep (poner el mismo)
	return (0);
}
*/
static void	*thread_lives(void *arg)
{
	t_philo_args	*philo;

	philo = (t_philo_args *)arg;
	while (philo->life == 0)
		usleep(50);
	while (1)
	{
		//if (check_loop(philo, &curr_time))
		//	return (NULL);
		if (pthread_mutex_lock(&(philo->args->mutex_death)))
			perror("thread_lives: mutex_lock mutex_death");
		if (philo->args->end == 1)
		{
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		if (philo->args->mu_since > philo->life)
		{
			print_msg(philo, 'd'); //00! antes o despues de setear end = 1?
			philo->args->end = 1;
			pthread_mutex_unlock(&(philo->args->mutex_death));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->args->mutex_death));
		usleep(200);// coordinar con get_time usleep (poner el mismo)
	}
	return (NULL);
}

int	send_check_lives(t_philo_args *philo)
{
	if (pthread_create(&(philo->lives_id), NULL, &thread_lives, (void *)philo))
	{
		perror("send_check_lives: pthread_create:");
		return (1);
	}
	return (0);
}
