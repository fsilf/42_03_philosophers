/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:52:35 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 17:15:22 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static int	set_init_time(t_args *args)
{
	struct timeval	init_time;

	gettimeofday(&init_time, NULL);
	args->ms_init = convert_to_milisecs(&init_time);
	return (0);
}

static int	set_philo_lives(t_args *args, long unsigned **philo_lives)
{
	ssize_t	i;

	*philo_lives = NULL;
	*philo_lives = (long unsigned *)malloc(sizeof (long unsigned) * \
											args->num_philo);
	if (*philo_lives == NULL)
	{
		perror("set_philo_lives malloc:");
		return (1);
	}
	i = 0;
	while (i < args->num_philo)
	{
		(*philo_lives)[i] = args->ms_init + (long unsigned)args->time_life;
		i++;
	}
	return (0);
}

static int	set_structures(t_args *args, long unsigned **philo_lives, \
						t_queue_args **queue_args, t_philo_args **philo_args)
{
	set_init_time(args);
	if (set_philo_lives(args, philo_lives))
		return (1);
	if (set_queue_args(queue_args, args))
	{
		free_main(*philo_lives, *queue_args, *philo_args);
		return (1);
	}
	test_print_args(args);
	test_print_philo_lives(args, *philo_lives);
	test_print_queue_args(*queue_args);
	if (set_philo_args(args, *philo_lives, *queue_args, philo_args))
	{
		free_main(*philo_lives, *queue_args, *philo_args);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	long unsigned	*philo_lives;
	t_queue_args	*queue_args;
	t_philo_args	*philo_args;

	philo_args = NULL;
	queue_args = NULL;
	philo_lives = NULL;
	ft_memset(&args, -1, sizeof (t_args));
	if (process_argv(argc, argv, &args))
		return (1);
	set_structures(&args, &philo_lives, &queue_args, &philo_args);
	set_threads(queue_args, philo_args);
	free_main(philo_lives, queue_args, philo_args);
	return (0);
}
