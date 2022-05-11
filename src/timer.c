/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:59:50 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/11 20:04:21 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

int	add_ms(struct timeval tv, long unsigned to_add, struct timeval *res)
{
	res->tv_usec = \
		((long unsigned)tv.tv_usec + (to_add * 1000)) % 1000000;
	res->tv_sec = tv.tv_sec + \
		((long unsigned)tv.tv_usec + (to_add * 1000)) / 1000000;
	return (0);
}

/*
int	compare_mu(long unsigned mu_end, long unsigned mu_since)
{
	if (mu_since > mu_end)
		return (1);
	return (0);
}

int	compare_timevals(struct timeval end, struct timeval curr)
{
	if (curr.tv_sec > end.tv_sec)
		return (1);
	else if (curr.tv_sec == end.tv_sec)
	{
		if (curr.tv_usec >= end.tv_usec)
			return (1);
	}
	return (0);
}
*/

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
		if(mu_since >= mu_end)
			return (0);
		usleep(200);// coordinar con usleep de get_time
	}
}

unsigned	convert_to_milisecs(struct timeval time_all)
{
	unsigned	time_ms;

	time_ms = time_all.tv_sec * 1000 + (time_all.tv_usec / 1000);
	return (time_ms);
}

long unsigned	convert_to_microsecs(struct timeval time_all)
{
	long unsigned	time_mu;

	time_mu = 0;
	time_mu = (long unsigned)time_all.tv_sec * 1000000;
	time_mu = time_mu + (long unsigned)time_all.tv_usec;
	return (time_mu);
}
