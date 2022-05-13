/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:09:49 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 03:25:22 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct args
{
	ssize_t			num_philo;
	ssize_t			time_life;
	ssize_t			time_eat;
	ssize_t			time_sleep;
	ssize_t			num_loops;
	ssize_t			end;
	long unsigned	mu_since;
	ssize_t			seated;
	ssize_t			philo;
	sem_t			*forks;
	sem_t			*sem_death;
	sem_t			*sem_philo;
	sem_t			*sem_print;
	sem_t			*sem_start;
	sem_t			**counter;
	struct timeval	tv_init;
	long unsigned	mu_init;
}				t_args;

typedef struct s_id_store
{
	pid_t		*philo_ids;
	pid_t		loops_id;
	pthread_t	get_time_id;
}	t_id_store;

typedef struct s_philo_args
{
	t_args			*args;
	ssize_t			philo;
	sem_t			*sem_counter;
	ssize_t			counter;
	long unsigned	life;
	long unsigned	mu_start_action;			
	pthread_t		lives_id;
	pthread_t		get_time_id;
}	t_philo_args;

ssize_t			atoi_philo(const char *str, ssize_t *ptr_num);
int				add_num_loops(t_philo_args *philo);
long unsigned	convert_to_microsecs(struct timeval time_all);
int				custom_sleep(t_philo_args *philo, ssize_t ms_to_wait);
void			*ft_memset(void *str, int c, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
int				philo_cycle(t_philo_args *philo);
int				print_msg(t_philo_args *philo, char type);
int				process_argv(int argc, char **argv, t_args *args);
int				send_check_lives(t_philo_args *philo);
int				send_check_num_loops(t_args *args, pid_t *loop_id);
int				send_get_time(t_args *args, pthread_t *get_time_id);
int				send_start_philos(t_args *args, t_id_store *pids);
int				set_processes(t_args *args);
void			test_print_args(t_args args);
void			test_print_timeval(struct timeval tv);
int				unlink_semaphores(t_args args);
#endif
