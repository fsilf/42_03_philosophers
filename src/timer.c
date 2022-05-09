/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:59:50 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/09 04:18:29 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include "philo.h"

/*
long unsigned	ft_timesub(long unsigned ms_start, long unsigned ms_end)
{
	long unsigned	res;

	res = 0;
	if (ms_start > ms_end)
		res = ms_start - ms_end;
	else
		res = 0;
	return (res);
}

long unsigned	ft_timeadd(long unsigned ms_start, long unsigned ms_end)
{
	long long unsigned	res;

	res = 0;
	res = ms_start + ms_end;
	if (res > LONG_MAX)
	{
		write(2, "ft_timeadd: result out of bounds\n", 33);
		return (0);
	}
	return (res);
}
*/
/*
int	ft_timesub(struct timeval start, struct timeval end, struct timeval *res)
{
	if (end.tv_sec >= start.tv_sec)
		*res->tv_sec = end.tv_sec - start.tv_sec;
	else
	{
		*res->tv_sec = 0;
		*res->tv_usec = 0;
	}
	if (end.tv_usec >= start.tv_usec)
		*res->tv_usec = end.tv_usec - start.tv_usec;
	else
	{
		*res->tv_usec = start.tv_usec - end.tv_usec;
		if (*res->tv_sec == 0)
			*res->tv_usec = 0;
		else
			*res->tv_sec = *res->tv_sec - 1;
	}
	return (0);
}
int	copy_timevals(struct timeval ori, struct timeval *dest)
{
	dest->tv_usec = ori.tv_usec;
	dest->tv_sec = ori.tv_sec;
	return (0);
}
*/

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

int	custom_sleep(t_args *args, struct timeval end)
{
	struct timeval	curr_time;

	ft_memset(&curr_time, 0, sizeof (struct timeval));
	while (1)
	{
		gettimeofday(&curr_time, NULL);
		if (compare_timevals(end, curr_time))
			return (0);
		pthread_mutex_lock(&(args->mutex_death));
		if (check_death(args->end, &(args->mutex_death)))
			return (1) ;
		pthread_mutex_unlock(&(args->mutex_death));
		usleep(100);
	}
}

/*
long unsigned	convert_to_milisecs(struct timeval *time_all)
{
	long unsigned	time_ms;

	time_ms = 0;
	time_ms = (long unsigned)time_all->tv_sec * 1000;
	time_ms = time_ms + (long unsigned)(time_all->tv_usec / 1000);
	return (time_ms);
}
*/
