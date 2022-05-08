/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:46:23 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 14:44:53 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static int	init_mutex_forks(pthread_mutex_t **mutex_fork, ssize_t num_philo)
{
	ssize_t	i;

	i = 0;
	*mutex_fork = NULL;
	*mutex_fork = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * \
												num_philo);
	if (*mutex_fork == NULL)
	{
		perror("init_mutex_fork: malloc:");
		return (1);
	}
	while (i < num_philo)
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
	}
	ft_memset(*forks, 0, sizeof (ssize_t) * num_philos);
	return (0);
}

int	set_forks(t_args *args)
{
	if (init_mutex_forks(&(args->mutex_fork), args->num_philo))
		return (1);
	if (init_forks(&(args->forks), args->num_philo))
		return (1);
	return (0);
}
