/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:08:56 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 14:21:30 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

int	unlink_semaphores(t_args args)
{
	ssize_t	i;
	char	name[4];

	i = 0;
	name[0] = 'c';
	name[1] = 'o';
	name[3] = '\0';
	while (i < args.num_philo)
	{
		name[2] = (char)i + 48;
		sem_unlink(name);
		i++;
	}
	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("philo");
	sem_unlink("start");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	args;

	if (process_argv(argc, argv, &args))
		return (1);
	if (set_processes(&args))
		return (1);
	unlink_semaphores(args);
	free(args.counter);
	return (0);
}
