/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:51:51 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 13:52:58 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "philo_bonus.h"

int	set_philo_args(t_args *args, t_philo_args *philo)
{
	char	name[4];

	name[0] = 'c';
	name[1] = 'o';
	name[3] = '\0';
	ft_memset(philo, 0, sizeof (t_philo_args));
	philo->philo = args->philo;
	name[2] = philo->philo + 48;
	philo->args = args;
	philo->args->sem_death = sem_open("death", O_RDWR);
	philo->args->sem_philo = sem_open("philo", O_RDWR);
	philo->args->forks = sem_open("forks", O_RDWR);
	philo->args->sem_print = sem_open("print", O_RDWR);
	philo->args->sem_start = sem_open("start", O_RDWR);
	philo->life = args->mu_init + (args->time_life * 1000);
	philo->sem_counter = sem_open(name, O_RDWR);
	return (0);
}
