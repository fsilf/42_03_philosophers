/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_start_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:26:48 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/04 21:24:49 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	init_pthread_philo_id(pthread_t **pthread_philo_id)
{
	*pthread_philo_id = NULL;
	*pthread_philo_id = (pthread_t *)malloc(sizeof (pthread_t) *\
		   					args->num_philos);
	if (*pthread_philo_id == NULL)
	{
		perror("send_start_philos: malloc");
		return (1);
		//gestionar exits
	}
	ft_memset(*pthread_philo_id, 0, sizeof (pthread_t) * args->num_philos);
	return (0);
}

static int	wait_for_threads(t_args *args, pthread_t *pthread_philo_id)
{
	ssize_t			i;

	i = 0;
	while (i < args->num_philos)
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

static int	init_philo_threads(t_args *args, pthread_t *pthread_philo_id, \
								t_philo_args *philo_args)
{
	ssize_t			i;
	pthread_mutex_t	mutex_philo;

	i = 0;
	pthread_mutex_init(&mutex_philo, NULL);
	philo_args->mutex_philo = &mutex_philo;
	while (i < args->num_philos)
	{
		pthread_mutex_lock(&philo_mutex);
		philo_args->philo = i;
		pthread_mutex_unlock(&philo_mutex);
		if (pthread_create(&(pthread_philo_id[i]), NULL, &thread_philo, \
								philo_args));
		{
			perror("send_start_philos: pthread_create");
			free_philo_args(philo_args, args);
			pthread_mutex_destroy(&philo_mutex);
			free(pthread_philo_ids);
			return (1);
			//gestionar exits
		}
		i++;
	}
	pthread_mutex_destroy(&philo_mutex);
	return (0);
}

static int	init_mutex_forks(pthread_mutex_t **mutex_fork, t_args *args)
{
	ssize_t	i;

	i = 0;
	*mutex_fork = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) *\
		   										args->num_philo);
	if (*mutex_fork == NULL)
	{
		perror("init_mutex_fork: malloc:");
		return (1);
		//gestionar exit
	}
	while (i < args->num_philo)
	{
		if (pthread_mutex_init(&((*mutex_fork)[i])))
		{
			perror("init_mutex_fork: mutex_init:")
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_forks(ssize_t **forks, ssize_t	num_philos)
{
	*forks = NULL;
	*forks = (ssize_t *)malloc(sizeof (ssize_t) * num_philos);
	if (*forks = NULL)
	{
		perror ("init_forks: malloc");
		return (1);
		//gestionar exits
	}
	ft_memset(*forks, 0, sizeof (ssize_t) * num_philos);
	return (0);
}

static int	set_philo_args(t_args *args, ssize_t *philo_lives, \
							t_queue_args *queue_args, t_philo_args **philo_args)
{
	pthread_mutex_t	*mutex_fork;
	ssize_t			*forks;

	*philo_args = NULL;
	*philo_args = (t_philo_args *)malloc(sizeof (t_philo_args));
	(*philo_args)->args = args;
	(*philo_args)->philo_lives = philo_lives;
	(*philo_args)->head_log = queue_args->head_log;
	if (init_mutex_forks(&mutex_fork))
		return (1);
	//gestionar exits
	(*philo_args)->mutex_fork = mutex_fork;
	(*philo_args)->mutex_philo = NULL;
	(*philo_args)->philo = -1;
	if (init_forks(&forks, args->num_philos))
		return (1);
	(*philo_args)->forks = forks;
	return (0);
}

int	send_start_philos(t_args *args, ssize_t *philo_lives, \
						t_queue_args *queue_args)
{
	pthread_t		*pthread_philo_id;
	ssize_t			i;
	t_philo_args	*philo_args;

	if (init_pthread_philo_id(&pthread_philo_id))
		return (1);
	if (set_philo_args(t_args *args, ssize_t *philo_lives, \
				t_queue_args *queue_args, &philo_args))
		return (1);
	if (init_philo_threads(args, pthread_philo_id, philo_args))
		return (1);
	if (wait_for_philo_threads(args, pthread_philo_id))
	{
		free(pthread_philo_ids);
		return (1);
		//gestionar exits
	}
	free(pthread_philo_ids);
	free_philo_args(philo_args, args);
	return(0);
}
