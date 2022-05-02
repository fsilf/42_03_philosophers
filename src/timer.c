/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:59:50 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/02 14:51:27 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include "philo.h"

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
long unsigned	convert_to_milisecs(struct timeval *time_all)
{
	long unsigned	time_ms;

	time_ms = 0;
	time_ms = (long unsigned)time_all->tv_sec * 1000;
	time_ms = time_ms + (long unsigned)(time_all->tv_usec / 1000);
	return (time_ms);
}
