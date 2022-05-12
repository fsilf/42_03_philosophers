/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:40:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/12 14:23:32 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	get_msg(char **msg, char type)
{
	if (type == 'f' || type == 'e')
		*msg = ft_strdup("has taken a fork");
	if (type == 'r')
		*msg = ft_strdup("is eating");
	if (type == 's')
		*msg = ft_strdup("is sleeping");
	if (type == 't')
		*msg = ft_strdup("is thinking");
	if (type == 'd')
		*msg = ft_strdup("has died");
}

int	print_msg(t_philo_args *philo, char type)
{
	long unsigned	ms_since;
	char			*msg;

	get_msg(&msg, type);
	pthread_mutex_lock(&(philo->args->mutex_print));
	ms_since = philo->args->mu_since;
	if (philo->args->end == 1)
	{
		free(msg);
		pthread_mutex_unlock(&(philo->args->mutex_print));
		return (1);
	}
	ms_since = ms_since / 1000;
	printf("%ld %zd %s\n", ms_since, philo->philo, msg);
	if (type == 'e')
	{
		free(msg);
		get_msg(&msg, 'r');
		printf("%ld %zd %s\n", ms_since, philo->philo, msg);
	}
	pthread_mutex_unlock(&(philo->args->mutex_print));
	free(msg);
	return (0);
}
