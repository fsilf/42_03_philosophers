/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:52:35 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/03 21:52:33 by fsilva-f         ###   ########.fr       */
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
	return (philo_lives)

}

static t_queue_args *set_queue_args(void)
{
}

int	main(int argc, char *argv[])
{
	t_args			args;
	ssize_t			*philo_lives;
	t_queue_args	*queue_args;

	ft_memset(&args, -1, sizeof (t_args));
	if (process_argv(argc, argv, &args))
		return (1);
	set_init_time(&args);
	philo_lives = set_philo_lives(args);
	if (philo_lives == NULL)
		return (1);
	test_print_args(&args);
	//00! working build arguments for check_life.c
	queue_args = set_queue_args()
	send_philo_lives()
	free(philo_lives);
	return (0);
}
