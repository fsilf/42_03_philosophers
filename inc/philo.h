/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:58:28 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/14 12:33:42 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <unistd.h>

typedef struct timeval	t_timeval;

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
	t_timeval		*init_tv;
}				t_pick_fork;

ssize_t	atoi_philo(const char *str, ssize_t *ptr_num);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int		process_argv(int argc, char **argv, t_args *args);
void	test_print_args(t_args *args);

#endif
