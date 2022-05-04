/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_queue_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:43 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 12:15:22 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static int	init_head_log(t_log ***head_log)
{
	*head_log = NULL;
	*head_log = (t_log **)malloc(sizeof (t_log *));
	if (*head_log == NULL)
	{
		perror("set_queue_args head_log malloc");
		return (1);
	}
	**head_log = NULL;
	return (0);
}

static int	init_mutex_queue(pthread_mutex_t **mutex_queue)
{
	*mutex_queue = NULL;
	*mutex_queue = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t));
	if (*mutex_queue == NULL)
	{
		perror("set_queue_args mutex_queue malloc");
		return (1);
	}
	if (pthread_mutex_init(*mutex_queue, NULL))
	{
		perror("mutex_init queue:");
		return (1);
	}
	return (0);
}

static int	init_queue_args(t_queue_args **queue_args, \
							t_log **head_log, pthread_mutex_t *mutext_queue)
{
	*queue_args = NULL;
	*queue_args = (t_queue_args *)malloc(sizeof (t_queue_args));
	if (*queue_args == NULL)
	{
		perror("set_queue_args: queue_args malloc:")
		return (1);
	}
	(*queue_args)->head_log = head_log;
	(*queue_args)->mutex = mutex_queue;
	(*queue_args)->log = NULL;
	return (0);
}

int	t_queue_args *set_queue_args(void)
{
	t_log			**head_log;
	t_queue_args	*queue_args;
	pthread_mutex_t	*mutex_queue;

	if (init_head_log(&head_log))
		return (1);
	if (init_mutex_queue(&mutex_queue))
		return (1);
	if (init_queue_args(&queue_args, head_log, mutex_queue))
		return (1);
	return (0);
}
