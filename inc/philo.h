/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:58:28 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/12 20:09:25 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct timeval	t_timeval;

typedef struct s_pick_fork
{
	pthread_mutex_t	*forkl_lock;
	pthread_mutex_t	*forkr_lock;
	ssize_t			time_to_eat;
	ssize_t			*forkl_num;
	ssize_t			*forkr_num;
	ssize_t			*philo_num;
	char			*philo_str;
	t_timeval		*init_tv;
}				t_pick_fork;

#endif
