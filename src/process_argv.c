/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:06:22 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 15:01:33 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
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

int	process_argv(int argc, char **argv, t_args *args)
{
	int	err;

	err = 0;
	if (args == NULL)
		error_args("argv is NULL\n", &err);
	else if (argc < 5 || argc > 6)
		error_args("wrong number of arguments\n", &err);
	if (err == 1)
		return (err);
	if (atoi_philo(argv[1], &(args->num_philo)))
		error_args("wrong format num_philosophers\n", &err);
	if (atoi_philo(argv[2], &(args->time_life)))
		error_args("wrong format time_to_die\n", &err);
	if (atoi_philo(argv[3], &(args->time_eating)))
		error_args("wrong format num_to_eat\n", &err);
	if (atoi_philo(argv[4], &(args->time_unhungry)))
		error_args("wrong format time_to_sleep\n", &err);
	if (argv[5] != NULL)
	{
		if (atoi_philo(argv[5], &(args->num_loops)))
			error_args(\
			"wrong format number_of_times_a_philosopher_must_eat\n", &err);
	}
	args->time_think = 5;//00! check different values
	return (err);
}
