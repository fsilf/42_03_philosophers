/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:06:18 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 14:22:00 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <phtread.h>
#include <stdlib.h>
#include "philo.h"

int	free_queue_args(t_queue_args *queue_args)
{
	pthread_mutex_destroy(queue_args->mutex);
	free(queue_args->mutex);
	log_free_all(queue_args->head_log);
	free(queue_args);
	return (0);
}
