/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:12:04 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/03 18:27:26 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

void	test_print_args(t_args *args)
{
	printf("num_philo:%zd\n", args->num_philo);
	printf("time_life:%zd\n", args->time_life);
	printf("time_eating:%zd\n", args->time_eating);
	printf("time_unhungry:%zd\n", args->time_unhungry);
	printf("num_loops:%zd\n", args->num_loops);
}

void	test_print_timeval(struct timeval *tv)
{
	printf("secs:%d, usecs:%d\n", \
			(unsigned int)tv->tv_sec, (unsigned int)tv->tv_usec);
}
