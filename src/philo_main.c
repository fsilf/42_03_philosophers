/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:52:35 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 22:18:24 by fsilva-f         ###   ########.fr       */
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

static int	set_end_and_mutex(t_args *args)
{
	args->end = 0;
	if (pthread_mutex_init(&(args->mutex_end), NULL))
	{
		perror("set_end_and_mutex: mutex init:");
		return (1);
	}
	return (0);
}

static int	wait_for_philo_threads(t_args *args, pthread_t *pthread_philo_id)
{
	ssize_t	i;

	i = 0;
	while (i < args->num_philo)
	{
		if (pthread_join(pthread_philo_id[i], NULL))
		{
			perror("send_start_philos: pthread_detach");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	send_threads_and_wait(t_args *args, long unsigned *philo_lives, \
									t_queue_args *queue_args)
{
	t_id_store		pthread_ids;//!00 working here=> ids for all the thread groups

	if (send_start_philos(args, philo_lives, queue_args, \
							pthread_ids.pthread_philo_ids))
	{
		free_main(philo_lives, queue_args, args);
		return (1);
	}	
	printf("llega aqui?\n");
	send_check_lives(args, philo_lives, queue_args, pthread_ids.pthread_lives_id);
	printf("y aqui?\n");
	send_printing_queue(queue_args, pthread_ids.pthread_print_id);
	// waits (order)?
	if (pthread_join(*(pthread_ids.pthread_lives_id), NULL))
	{
		perror("send_check_live: thread_join");
		return (1);
	}
	if (wait_for_philo_threads(args, pthread_ids.pthread_philo_ids))
	{
		free(pthread_ids.pthread_philo_ids);
		return (1);
		//gestionar exits
	}
	//if (pthread_join(*pthread_print_id, &resval))
	if (pthread_join(*(pthread_ids.pthread_print_id), NULL))
	{
		perror("send_printing_queue: pthread_join");
		return (1);
	}
	//free_pthread_ids?
	free(pthread_ids.pthread_philo_ids);
	//free_philos_args(philo_args, args); needs philo_args in main
	return (0);
}
int	main(int argc, char *argv[])
{
	t_args			args;
	long unsigned	*philo_lives;
	t_queue_args	*queue_args;

	ft_memset(&args, -1, sizeof (t_args));
	if (process_argv(argc, argv, &args))
		return (1);
	set_init_time(&args);
	if (set_end_and_mutex(&args))
		return (1);
	test_print_args(&args);
	if (set_philo_lives(&args, &philo_lives))
		return (1);
	test_print_philo_lives(&args, philo_lives);
	if (set_queue_args(&queue_args))
	{
		free_main(philo_lives, queue_args, &args);
		return (1);
	}
	test_print_queue_args(queue_args);
	send_threads_and_wait(&args, philo_lives, queue_args);
	/* send threads and wait for threads
	if (send_start_philos(&args, philo_lives, queue_args, \
							thread_ids->thread_philo_ids))
	{
		free_main(philo_lives, queue_args, &args);
		return (1);
	}	
	printf("llega aqui?\n");
	send_check_lives(&args, philo_lives, queue_args);
	printf("aqui no\n");
	send_printing_queue(queue_args);
	*/
	free_main(philo_lives, queue_args, &args);
	return (0);
}
