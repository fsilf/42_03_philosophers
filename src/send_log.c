/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:19:28 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 14:02:06 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "philo.h"

int	send_log(t_queue_args *queue_args, char detach)
{
	pthread_t	thread_add_id;

	if (pthread_create(&thread_add_id, NULL, &thread_log_add, &queue_args))
	{
		perror("send_log: pthread_create");
		return (1);
	}
	if (detach == 'y')
	{
		if (pthread_detach(thread_add_id))
		{
			perror("send log: pthread_detach");
			return (1);
		}
	}
	else
	{
		if (pthread_join(thread_add_id, NULL))
		{
			perror("send_log: pthread_join");
			return (1);
		}
	}
	return (0);
}
