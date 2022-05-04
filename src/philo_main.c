/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:52:35 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 14:26:00 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

static int	set_init_time(t_args *args)
{
	struct timeval	init_time;

	gettimeofday(&init_time, NULL);
	args->ms_init = convert_to_milisecs(&init_time);
	return (0);
}

static ssize_t	*set_philo_lives(t_args args)
{
	ssize_t	*philo_lives;
	ssize_t	i;

	philo_lives = NULL;
	philo_lives = (ssize_t *)malloc(sizeof (ssize_t) * args.num_philo);
	if (philo_lives == NULL)
	{
		perror("set_philo_lives malloc:");
		return (NULL);
	}
	i = 0;
	while (i < args.num_philo)
	{
		philo_lives[i] = args.ms_init;
		i++;
	}
	return (philo_lives);
}


int	main(int argc, char *argv[])
{
	t_args			args;
	ssize_t			*philo_lives;
	t_queue_args	*queue_args;
	phtread_

	ft_memset(&args, -1, sizeof (t_args));
	if (process_argv(argc, argv, &args))
		return (1);
	set_init_time(&args);
	philo_lives = set_philo_lives(args);
	if (philo_lives == NULL)
		return (1);
	test_print_args(&args);
	if (set_queue_args(&queue_args))
		return (1);
	send_start_philos(args, philos_lives, queue_args);// 00! working create 
	send_check_lives(args, philo_lives, queue_args)
	free(philo_lives);
	free_queue_args(queue_args);
	return (0);
}
