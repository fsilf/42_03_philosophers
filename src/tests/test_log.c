/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:29:24 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/03 13:04:10 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

int main(void)
{
	t_log			**logs;
	t_log			**head_log;
	struct timeval	init_time;
	struct timeval	log_time;
	long unsigned	ms_init;
	long unsigned	ms_time;
	ssize_t			i;
	pthread_t		thread_print_id;
	pthread_t		thread_add_id;
	pthread_mutex_t	mutex_queue;
	t_queue_args	queue_args;
	//char			log_types[5] = {'f', 'e', 's', 't', 'd'};
	char			log_types[5] = {'d', 'e', 's', 't', 'f'};
	ssize_t			philos[5] = {1, 2, 3, 4, 5};
	void			*resval;

	logs = NULL;
	logs = (t_log **)malloc(sizeof (t_log *) * 5);
	if (logs == NULL)
	{
		perror("logs malloc");
		return (1);
	}
	head_log = NULL;
	head_log = (t_log **)malloc(sizeof (t_log *));
	if (head_log == NULL)
	{
		perror("head_log malloc");
		return (1);
	}
	*head_log = NULL;
	gettimeofday(&init_time, NULL);
	ms_init = convert_to_milisecs(&init_time);
	printf("ms_init: %ld\n", ms_init);
	sleep(1);
	i = 0;
	if (pthread_mutex_init(&mutex_queue, NULL))
	{
		perror("mutex_init queue:");
		return (1);
	}
	queue_args.head_log = head_log;
	queue_args.mutex = &mutex_queue;
	while (i < 5)
	{
		ft_memset(&log_time, 0, sizeof (struct timeval));
		gettimeofday(&log_time, NULL);
		ms_time = 0;
		ms_time = convert_to_milisecs(&log_time);
		printf("ms_time log[%zd]: %ld\n", i, ms_time);
		ms_time = ft_timesub(ms_time, ms_init);
		printf("ms_time after sub log[%zd]: %ld\n", i, ms_time);
		ms_time = ms_time - (10 * i);
		logs[i] = log_new(ms_time, log_types[i], philos[i]);
		queue_args.log = logs[i];
		if (pthread_create(&thread_add_id, NULL, &thread_log_add, &queue_args))
		{
			perror("pthread_create log_add");
			return (1);
		}
		if (pthread_detach(thread_add_id))
		{
			perror("pthread_detach log_add");
			return (1);
		}
		usleep(1000);
		i++;
	}
	if (pthread_create(&thread_print_id, NULL, &thread_print_queue, &queue_args))
	{
		perror("pthread_create queue");
		return (1);
	}
	if (pthread_join(thread_print_id, &resval))
	{
		perror("pthread_join queue");
		return (1);
	}
	if ((char *)resval != NULL)
	{
		printf("error in log_print_loop:%s\n", (char *)resval);
		free(resval);
		log_free_all(head_log);
		return (1);
	}
	free(resval);
	log_free_all(head_log);
	return (0);
}
