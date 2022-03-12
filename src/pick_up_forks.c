/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_up_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:14:41 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/12 20:08:51 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

ssize_t	calculate_diff_in_milisecs(t_timeval *end_time, t_timeval *start_time)
{
	t_timeval	curr_time;

		milisecs = (ssize_t)((curr_time.tv_sec - start_time.tv_sec) * 1000);
	milisecs = (ssize_t)((curr_time.tv_sec - start_time.tv_sec) * 1000);
	/*
	milisecs = milisecs + (ssize_t)((time_eat.tv_usec - fork_store->init_tv.tv_usec)\
	milisecs = milisecs + (ssize_t)((time_eat.tv_usec - fork_store->init_tv.tv_usec)\
									/ 1000);
	*/
}

int	philo_eat()
{
	t_timeval	eat_start;
	t_timeval	curr_time;
	useconds_t	microsecs;
	if (gettimeofday(&eat_start, NULL))
	{
		perror("philo_eat: gettimeofday:");
		exit(EXIT_FAILURE);
	}
	msg_eating();
	milisecs = calculate_diff_in_milisecs(fork_store->init_tv);
	mgs = itoa_ssize_t(milisecs);
	mgs = ft_strjoin_f(msg, " ");
	msg = ft_strjoin_f(msg, fork_store->philo_str);
	msg = ft_strjoin_f()
	write(1, )
	if (gettimeofday(&curr_time, NULL))
	{
		perror("philo_eat: gettimeofday:");
		exit(EXIT_FAILURE);
	}
	milisecs = calculate_diff_in_milisecs(curr_time, eat_start);
	microsecs = (useconds_t)(milisecs * 1000);
	usleep(microsecs); //here ok?
	return (0);
}

void	*pick_up_forks(void *pick_fork_store)
{
	t_pick_fork	*fork_store;
	char			*msg;
	t_timeval		time_eat;
	ssize_t			milisecs;
	
	fork_store = (t_fork *)pick_fork_store;
	pthread_mutex_lock(fork_store->forkl_lock);
	msg_take_fork()
	pthread_mutex_lock(fork_store->forkr_lock);
	msg_take_fork()
	if (philo_eat(time_to_eat))
	{
		perror("philo_eat:");
		exit(EXIT_FAILURE);
	}
}
