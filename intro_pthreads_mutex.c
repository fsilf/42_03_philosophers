/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_pthreads_mutex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:41 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/12 13:10:36 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

typedef struct	s_do_process
{
	pthread_mutex_t	*lock;
	ssize_t			*counter;
}				t_do_process;

void	*do_process(void *store)
{
	t_do_process	*locstore;
	char			digit;			

	locstore = (t_do_process *)store;
	pthread_mutex_lock(locstore->lock);
	int i;

	i = 0;
	*(locstore->counter) = *(locstore->counter) + 1;
	while (i < 5)
	{
		//printf("%ld\n", *(locstore->counter));
		digit = *(locstore->counter) + '0';
		write(1, &digit, 1);
		sleep(1);
		i++;
	}
	write(1, "...Done\n", 8);
	pthread_mutex_unlock(locstore->lock);
	return (NULL);
}

int	main (void)
{
	//int	err;
	pthread_t		t1;
	pthread_t		t2;
	pthread_mutex_t	lock;
	ssize_t			counter;
	t_do_process	store;

	store.lock = &lock;
	store.counter = &counter;
	if (pthread_mutex_init(store.lock, NULL) != 0)
	{
		perror("Mutex init failed\n");
		return (1);
	}
	*store.counter = 0;
	printf("%ld\n", *(store.counter));
	pthread_create(&t1, NULL, do_process, &store);
	pthread_create(&t2, NULL, do_process, &store);
	pthread_join(t2, NULL);
	pthread_join(t1, NULL);
	return (0);
}
