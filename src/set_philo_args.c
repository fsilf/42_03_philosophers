/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:36:11 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 14:04:38 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	set_philo_args(t_args *args, long unsigned *philo_lives, \
						t_queue_args *queue_args, t_philo_args *philo_args)
{
	pthread_mutex_t	*mutex_fork;
	ssize_t			*forks;

	//*philo_args = NULL;
	//*philo_args = (t_philo_args *)malloc(sizeof (t_philo_args));
	(*philo_args)->args = args;
	//(*philo_args)->philo_lives = philo_lives;
	//(*philo_args)->head_log = queue_args->head_log;
	//(*philo_args)->mutex_queue = queue_args->mutex;
	(*philo_args)->philo = -1;
	(*philo_args)->ms_init = args->ms_init;
	return (0);
}
