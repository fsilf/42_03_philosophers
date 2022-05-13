/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_get_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:57:07 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 16:31:53 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static void	*thread_get_time(void *arg)
{
	t_args			*args;
	struct timeval	curr_time;
	long unsigned	mu_curr;

	args = arg;
	if (args->num_philo == 1)
		return (NULL);
	while (args->end == 0)
	{
		gettimeofday(&curr_time, NULL);
		mu_curr = convert_to_microsecs(curr_time);
		mu_curr = mu_curr - args->mu_init;
		pthread_mutex_lock(&(args->mutex_death));
		args->mu_since = mu_curr;
		pthread_mutex_unlock(&(args->mutex_death));
		usleep(800);
	}
	return (NULL);
}

int	send_get_time(t_args *args, pthread_t *get_time_id)
{
	if (pthread_create(get_time_id, NULL, &thread_get_time, args))
	{
		perror("send_get_time: pthread_create");
		return (1);
	}
	return (0);
}
