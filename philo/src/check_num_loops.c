/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_loops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:50:25 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 14:20:10 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num_loops(t_philo_args *philo)
{
	ssize_t	i;

	if (philo->args->num_loops == 0)
		return (0);
	(philo->args->counter)[philo->philo] = \
								(philo->args->counter)[philo->philo] + 1;
	i = 0;
	while (i < philo->args->num_philo)
	{
		if ((philo->args->counter)[i] < philo->args->num_loops)
			return (0);
		i++;
	}
	pthread_mutex_lock(&(philo->args->mutex_death));
	philo->args->end = 1;
	pthread_mutex_unlock(&(philo->args->mutex_death));
	return (1);
}
