/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:46:17 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/05 13:46:52 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

int	check_death(t_philo_args *philo_args)
{
	pthread_mutex_lock(&(philo_args->args->mutex_end));
	if (philo_args->args->end == 1)
		return (1);
	pthread_mutex_unlock(&(philo_args->args->mutex_end));
	return (0);
}
