/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:36:11 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 17:27:20 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static int	init_mutex_forks(pthread_mutex_t **mutex_fork, t_args *args)
{
	ssize_t	i;

	i = 0;
	*mutex_fork = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * \
												args->num_philo);
	if (*mutex_fork == NULL)
	{
		perror("init_mutex_fork: malloc:");
		return (1);
		//gestionar exit
	}
	while (i < args->num_philo)
	{
		if (pthread_mutex_init(&((*mutex_fork)[i]), NULL))
		{
			perror("init_mutex_fork: mutex_init:");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_forks(ssize_t **forks, ssize_t	num_philos)
{
	*forks = NULL;
	*forks = (ssize_t *)malloc(sizeof (ssize_t) * num_philos);
	if (*forks == NULL)
	{
		perror ("init_forks: malloc");
		return (1);
		//gestionar exits
	}
	ft_memset(*forks, 0, sizeof (ssize_t) * num_philos);
	return (0);
}

int	set_philo_args(t_args *args, long unsigned *philo_lives, \
						t_queue_args *queue_args, t_philo_args **philo_args)
{
	pthread_mutex_t	*mutex_fork;
	ssize_t			*forks;

	*philo_args = NULL;
	*philo_args = (t_philo_args *)malloc(sizeof (t_philo_args));
	(*philo_args)->args = args;
	(*philo_args)->philo_lives = philo_lives;
	(*philo_args)->head_log = queue_args->head_log;
	if (init_mutex_forks(&mutex_fork, args))
		return (1);
	//gestionar exits
	(*philo_args)->mutex_fork = mutex_fork;
	pthread_mutex_init(&((*philo_args)->mutex_philo), NULL);
	(*philo_args)->mutex_queue = queue_args->mutex;
	(*philo_args)->philo = -1;
	if (init_forks(&forks, args->num_philo))
		return (1);
	(*philo_args)->forks = forks;
	(*philo_args)->ms_init = args->ms_init;
	return (0);
}
