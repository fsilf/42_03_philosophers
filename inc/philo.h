/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:58:28 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/02 14:53:12 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <unistd.h>

typedef struct	args
{
	ssize_t	num_philo;
	ssize_t	time_life;
	ssize_t	time_eating;
	ssize_t	time_unhungry;
	ssize_t	num_loops;
}				t_args;

typedef struct s_pick_fork
{
	pthread_mutex_t	*forkl_lock;
	pthread_mutex_t	*forkr_lock;
	ssize_t			time_to_eat;
	ssize_t			*forkl_num;
	ssize_t			*forkr_num;
	ssize_t			*philo_num;
	char			*philo_str;
	struct timeval	*init_tv;
}				t_pick_fork;

ssize_t			atoi_philo(const char *str, ssize_t *ptr_num);
long unsigned	convert_to_milisecs(struct timeval *time_all);
void			*ft_memset(void *str, int c, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
long unsigned	ft_timeadd(long unsigned ms_start, long unsigned ms_end);
long unsigned	ft_timesub(long unsigned ms_start, long unsigned ms_end);
int				process_argv(int argc, char **argv, t_args *args);
void			test_print_args(t_args *args);
void			test_print_timeval(struct timeval *tv);

#endif
