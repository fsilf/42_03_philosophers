/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:59:50 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 14:22:35 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	custom_sleep(t_philo_args *philo, ssize_t ms_to_wait)
{
	long unsigned	mu_since;
	long unsigned	mu_end;

	pthread_mutex_lock(&(philo->args->mutex_death));
	mu_since = philo->args->mu_since;
	pthread_mutex_unlock(&(philo->args->mutex_death));
	mu_end = mu_since + (ms_to_wait * 1000);
	while (1)
	{
		if (philo->args->end == 1)
			return (1);
		pthread_mutex_lock(&(philo->args->mutex_death));
		mu_since = philo->args->mu_since;
		pthread_mutex_unlock(&(philo->args->mutex_death));
		if (mu_since >= mu_end)
			return (0);
		usleep(200);
	}
}

long unsigned	convert_to_microsecs(struct timeval time_all)
{
	long unsigned	time_mu;

	time_mu = 0;
	time_mu = (long unsigned)time_all.tv_sec * 1000000;
	time_mu = time_mu + (long unsigned)time_all.tv_usec;
	return (time_mu);
}
