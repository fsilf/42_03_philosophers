/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:58:28 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 20:09:28 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct args
{
	ssize_t			num_philo;
	ssize_t			time_life;
	ssize_t			time_eating;
	ssize_t			time_unhungry;
	ssize_t			num_loops;
	ssize_t			*forks;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_philo;
	pthread_mutex_t	mutex_start;
	ssize_t			end;
	ssize_t			philo;
	struct timeval	tv_init;
}				t_args;

typedef struct	s_id_store
{
	pthread_t	*philo_ids;
	//pthread_t	print_id;
}	t_id_store;

typedef struct s_philo_args
{
	t_args			*args;
	ssize_t			philo;
	struct timeval	life;
	struct timeval	tv_begin;
	struct timeval	tv_end;
	ssize_t			fork1;
	ssize_t			fork2;
	pthread_t		lives_id;
	//t_log			**head_log;
	//pthread_mutex_t	*mutex_queue;
}	t_philo_args;

/*
typedef struct s_log
{
	char			type;
	long unsigned	time;
	ssize_t			num;
	ssize_t			philo;
	struct s_log	*prev;
	struct s_log	*next;
}	t_log;

typedef struct s_queue_agrs
{
	t_log			**head_log;
	pthread_mutex_t	*mutex;
	t_log			*log;
	ssize_t			philo;
	long unsigned	ms_init;
}	t_queue_args;
*/

/*
typedef struct s_check_life
{
	t_args			**args;
	long unsigned	*philo_lives;
	t_queue_args	*queue_args;
}	t_check_life;
*/
int				add_ms(struct timeval tv, long unsigned to_add, \
						struct timeval *res);
ssize_t			atoi_philo(const char *str, ssize_t *ptr_num);
int				cleanup_forks(ssize_t *forks, pthread_mutex_t *mutex_fork, \
								ssize_t num_philo);
int				compare_timevals(struct timeval end, struct timeval curr);
void			*ft_memset(void *str, int c, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
int				process_argv(int argc, char **argv, t_args *args);
int				send_check_lives(t_philo_args *philo);
int				send_start_philos(t_args *args, t_id_store *pthread_ids);
int				set_forks(t_args *args);
int				set_threads(t_args *args);
void			test_print_args(t_args args);
void			test_print_timeval(struct timeval tv);
/*
int				check_lives(t_args **args, long unsigned *philo_lives, \
					t_queue_args *queue_args);
int				check_death(t_philo_args *philo_args);
long unsigned	convert_to_milisecs(struct timeval *time_all);
int				free_main(long unsigned *philo_lives, \
							t_queue_args *queue_args, t_philo_args *philo_args);
int				free_philo_args(t_philo_args *philo_args);
int				free_queue_args(t_queue_args *queue_args);
char			*ft_strdup(const char *s1);
long unsigned	ft_timeadd(long unsigned ms_start, long unsigned ms_end);
long unsigned	ft_timesub(long unsigned ms_start, long unsigned ms_end);
void			log_addback(t_log **head_log, t_log *new_log, \
						pthread_mutex_t *mutex_queue);
int				log_free_all(t_log **head_log);
t_log			*log_last(t_log *head_log);
t_log			*log_new(long unsigned time, char type, ssize_t philo);
int				log_print_loop(t_log **head_log, pthread_mutex_t *mutex_queue);
int				log_remove(t_log **head_log, t_log *to_remove);
t_log			*log_search_min(t_log **head_log);
int				philo_step(t_philo_args *philo_args, \
							t_queue_args *queue_args, char type);
int				send_log(t_queue_args *queue_args, char detach);
int				send_check_lives(t_philo_args *philo_args, \
						t_queue_args *queue_args, t_id_store *pthread_ids);
int				send_printing_queue(t_queue_args *queue_args, \
									t_id_store *pthread_ids);
int				send_start_philos(t_philo_args *philo_args, \
									t_id_store *pthread_ids);
int				set_local_queue_args(t_queue_args *queue_args, \
						t_queue_args **local_queue, long unsigned ms_time, \
						char type);
int				set_philo_args(t_args *args, long unsigned *philo_lives, \
						t_queue_args *queue_args, t_philo_args **philo_args);
int				set_queue_args(t_queue_args **queue_args, t_args *args);
int				set_threads(t_queue_args *queue_args, \
									t_philo_args *philo_args);
void			test_print_philo_lives(t_args *args, long unsigned *philo_lives);
void			test_print_queue_args(t_queue_args *queue_args);
void			*thread_lives(void *arg);
void			*thread_log_add(void *arg);
void			*thread_philo(void *arg);
void			*thread_print_queue(void *arg);
void			*thread_usleep(void *arg);
*/
#endif
