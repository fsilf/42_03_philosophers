/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:12:00 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/10 10:48:54 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static int	cleanup_forks(ssize_t *forks, pthread_mutex_t *mutex_fork)
{
	free(forks);
	if (mutex_fork == NULL)
	{
		write(2, "cleanup_forks: mutex_fork == NULL\n", 34);
		return (0);
	}
	free(mutex_fork);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			args;

	if (process_argv(argc, argv, &args))
	{
		cleanup_forks(args.forks, args.mutex_fork);
		return (1);
	}
	test_print_args(args);
	if (set_threads(&args))
	{
		cleanup_forks(args.forks, args.mutex_fork);
		return (1);
	}
	cleanup_forks(args.forks, args.mutex_fork);
	return (0);
}
