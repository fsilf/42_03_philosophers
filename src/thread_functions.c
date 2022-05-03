/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:24:32 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/03 12:59:00 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

void	*thread_print_queue(void *arg)
{
	t_queue_args	*queue_args;
	char			*res;

	queue_args = arg;
	res = NULL;
	//res = ft_strdup("nope");
	if (log_print_loop(queue_args->head_log, queue_args->mutex))
	{
		write(2, "log_print_loop error\n", 22);
		res = ft_strdup("error");
	}
	return (res);
}

void	*thread_log_add(void *arg)
{
	t_queue_args	*queue_args;

	queue_args = arg;
	log_addback(queue_args->head_log, queue_args->log, queue_args->mutex);
	return (NULL);
}