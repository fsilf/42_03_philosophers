/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:12:04 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/14 12:43:21 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void	test_print_args(t_args *args)
{
	printf("num_philo:%zd\n", args->num_philo);
	printf("time_life:%zd\n", args->time_life);
	printf("time_eating:%zd\n", args->time_eating);
	printf("time_unhungry:%zd\n", args->time_unhungry);
	printf("num_loops:%zd\n", args->num_loops);
}
