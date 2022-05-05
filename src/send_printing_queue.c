/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_printing_queue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:18:31 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 22:18:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	send_printing_queue(t_queue_args *queue_args, pthread_t *pthread_print_id)
{
	//pthread_t	pthread_print_id;
	//void			*resval;

	if (pthread_create(pthread_print_id, NULL, &thread_print_queue, queue_args))
	{
		perror("send_printing_queue: pthread_create");
		return (1);
	}
	/*
	if (pthread_join(*pthread_print_id, &resval))
	{
		perror("send_printing_queue: pthread_join");
		return (1);
	}
	*/
	/* needs to have resval in main move
	if ((char *)resval != NULL)
	{
		printf("error in log_print_loop:%s\n", (char *)resval);
		free(resval);
		return (1);
	}
	free(resval);
	*/
	return (0);
}
