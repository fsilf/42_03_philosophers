/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:40:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 16:55:17 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

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

	if (philo->args->end == 1)
		return (1);
	get_msg(&msg, type);
	sem_wait(philo->args->sem_print);
	ms_since = philo->args->mu_since;
	ms_since = ms_since / 1000;
	printf("%ld %zd %s\n", ms_since, philo->philo + 1, msg);
	if (type == 'e')
	{
		free(msg);
		get_msg(&msg, 'r');
		printf("%ld %zd %s\n", ms_since, philo->philo + 1, msg);
	}
	sem_post(philo->args->sem_print);
	free(msg);
	return (0);
}
