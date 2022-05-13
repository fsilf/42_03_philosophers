/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:06:22 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 02:50:44 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

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

static int	set_counter(t_args *args)
{
	ssize_t	i;
	char	name[4];

	i = 0;
	name[0] = 'c';
	name[1] = 'o';
	name[3] = '\0';
	while(i < args->num_philo)
	{
		name[2] = (char)i + 48;
		args->counter[i] = sem_open(name, O_CREAT | O_EXCL, 0660, 0);
		if (args->counter[i] == SEM_FAILED)
		{
			perror("set_semaphores: counter open");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_counter(t_args *args)
{
	if (args->num_loops <= 0)
		return (0);
	args->counter = NULL;
	args->counter = (sem_t **)malloc(sizeof (sem_t *) * args->num_philo);
	if (args->counter == NULL)
	{
		perror("init_counter: malloc");
		return (1);
	}
	ft_memset((args->counter), 0, sizeof(sem_t *) * args->num_philo);
	if (set_counter(args))
		return (1);
	return (0);
}

static int	set_semaphores(t_args *args)
{
	int	sval;

	unlink_semaphores(*args);
	args->forks = sem_open("forks", O_CREAT | O_EXCL, 0660, 0);
	if (args->forks == SEM_FAILED)
	{
		perror("set_semaphores: forks open");
		return (1);
	}
	sem_getvalue(args->forks, &sval);
	printf("forks:%d\n", sval);
	args->sem_death = sem_open("death", O_CREAT | O_EXCL, 0660, 1);
	if (args->sem_death == SEM_FAILED)
	{
		perror("set_semaphores: sem_death open");
		return (1);
	}
	sem_getvalue(args->sem_death, &sval);
	printf("death:%d\n", sval);
	args->sem_philo = sem_open("philo", O_CREAT, 0660, 1);
	if (args->sem_philo == SEM_FAILED)
	{
		perror("set_semaphores: sem_philo open");
		return (1);
	}
	args->sem_print = sem_open("print", O_CREAT, 0660, 1);
	if (args->sem_print == SEM_FAILED)
	{
		perror("set_semaphores: sem_print open");
		return (1);
	}
	args->sem_start = sem_open("start", O_CREAT, 0660, 1);
	if (args->sem_start == SEM_FAILED)
	{
		perror("set_semaphores: sem_start open");
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
	if (set_semaphores(args))
		return (1);
	if (init_counter(args))
		return (1);
	return (0);
}
