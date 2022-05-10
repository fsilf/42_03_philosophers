/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:59:50 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/10 14:56:10 by fsilva-f         ###   ########.fr       */
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

int	custom_sleep(struct timeval end)
{
	struct timeval	curr_time;

	ft_memset(&curr_time, 0, sizeof (struct timeval));
	while (1)
	{
		gettimeofday(&curr_time, NULL);
		if (compare_timevals(end, curr_time))
			return (0);
		usleep(200);
	}
}

int	custom_sleep_philo(struct timeval end, ssize_t num_philo)
{
	struct timeval	curr_time;

	ft_memset(&curr_time, 0, sizeof (struct timeval));
	while (1)
	{
		gettimeofday(&curr_time, NULL);
		if (compare_timevals(end, curr_time))
			return (0);
		usleep(1 * num_philo);
	}
}

void	ft_timesub(struct timeval init, struct timeval curr, \
					struct timeval *res)
{
	if (curr.tv_usec < init.tv_usec)
	{
		res->tv_usec = 1000000 - (init.tv_usec - curr.tv_usec);
		res->tv_sec = curr.tv_sec - init.tv_sec - 1;
	}
	else
	{
		res->tv_usec = curr.tv_usec - init.tv_usec;
		res->tv_sec = curr.tv_sec - init.tv_sec;
	}
}

void	ft_timesub_ms(struct timeval init, struct timeval curr, \
						unsigned *res_ms)
{
	if (curr.tv_usec < init.tv_usec)
	{
		*res_ms = ((curr.tv_sec - init.tv_sec - 1) * 1000) + \
					((1000000 - (init.tv_usec - curr.tv_usec)) / 1000);
	}
	else
	{
		*res_ms = ((curr.tv_usec - init.tv_usec) / 1000) + \
					((curr.tv_sec - init.tv_sec) * 1000);
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
