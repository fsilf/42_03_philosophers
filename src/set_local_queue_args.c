/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_queue_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:37:26 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 14:54:35 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	set_local_queue_args(t_queue_args *queue_args, \
			t_queue_args **local_queue, long unsigned ms_time, char type)
{
	*local_queue = (t_queue_args *)malloc(sizeof (t_queue_args));
	{
		perror("set_local_queue_args");
		return (1);
		//gestionar exits
	}
	(*local_queue)->head_log = queue_args->head_log;
	(*local_queue)->mutex = queue_args->mutex;
	(*local_queue)->philo = queue_args->philo;
	(*local_queue)->log = log_new(ms_time, type, queue_args->philo);
	return (0);
}
