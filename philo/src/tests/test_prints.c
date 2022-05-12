/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:12:04 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 11:11:18 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

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
	if (args.forks[0] == 0)
		printf("forks set\n");
	else
		printf("forks NOT set\n");
	if (args.mutex_fork != NULL && &(args.mutex_fork[0]) != 0)
		printf("mutex_fork set\n");
	else
		printf("mutex_forks NOT set\n");
	if (&(args.mutex_philo) != 0)
		printf("mutex_philo set\n");
	else
		printf("mutex_philo NOT set\n");
	printf("end:%zd\n", args.end);
	test_print_timeval(args.tv_init);
}
