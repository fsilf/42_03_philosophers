/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:06:22 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 14:20:21 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	error_args(char *str, int *err)
{
	char	*str_err;

	*err = 1;
	str_err = "process_argv: ";
	str_err = ft_strjoin(str_err, str);
	write(2, str_err, ft_strlen(str_err));
	free(str_err);
}

static void	get_input_args(int argc, t_args *args, char **argv, int *err)
{
	if (args == NULL)
		error_args("argv is NULL\n", err);
	else if (argc < 5 || argc > 6)
		error_args("wrong number of arguments\n", err);
	if (atoi_philo(argv[1], &(args->num_philo)))
		error_args("wrong format num_philosophers\n", err);
	if (atoi_philo(argv[2], &(args->time_life)))
		error_args("wrong format time_to_die\n", err);
	if (atoi_philo(argv[3], &(args->time_eat)))
		error_args("wrong format num_to_eat\n", err);
	if (atoi_philo(argv[4], &(args->time_sleep)))
		error_args("wrong format time_to_sleep\n", err);
	if (argv[5] != NULL)
	{
		if (atoi_philo(argv[5], &(args->num_loops)))
			error_args(\
			"wrong format number_of_times_a_philosopher_must_eat\n", err);
	}
}

static int	init_counter(t_args *args)
{
	if (args->num_loops == 0)
		return (0);
	args->counter = NULL;
	args->counter = (ssize_t *)malloc(sizeof (ssize_t) * args->num_philo);
	if (args->counter == NULL)
	{
		perror("init_counter: malloc");
		return (1);
	}
	ft_memset(args->counter, 0, sizeof(ssize_t) * args->num_philo);
	return (0);
}

static int	init_mutexes(t_args *args)
{
	if (pthread_mutex_init(&(args->mutex_philo), NULL))
	{
		perror("process_argv: mutex init mutex_philo");
		return (1);
	}
	if (pthread_mutex_init(&(args->mutex_death), NULL))
	{
		perror("process_argv: mutex init mutex_death");
		return (1);
	}
	if (pthread_mutex_init(&(args->mutex_print), NULL))
	{
		perror("process_argv: mutex init mutex_print");
		return (1);
	}
	return (0);
}

int	process_argv(int argc, char **argv, t_args *args)
{
	int	err;

	err = 0;
	ft_memset(args, 0, sizeof (t_args));
	get_input_args(argc, args, argv, &err);
	if (err == 1)
		return (1);
	if (set_forks(args))
		return (1);
	if (init_mutexes(args))
		return (1);
	if (init_counter(args))
		return (1);
	return (0);
}
