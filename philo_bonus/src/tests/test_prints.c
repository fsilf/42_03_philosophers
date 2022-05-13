/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:12:04 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 19:51:41 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philo_bonus.h"

void	test_print_timeval(struct timeval tv)
{
	printf("secs:%d, usecs:%d\n", \
			(unsigned int)tv.tv_sec, (unsigned int)tv.tv_usec);
}

void	test_print_args(t_args args)
{
	printf("num_philo:%zd\n", args.num_philo);
	printf("time_life:%zd\n", args.time_life);
	printf("time_eat:%zd\n", args.time_eat);
	printf("time_sleeping:%zd\n", args.time_sleep);
	printf("num_loops:%zd\n", args.num_loops);
	test_print_timeval(args.tv_init);
}
