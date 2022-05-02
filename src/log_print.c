/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:17:05 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/02 18:12:51 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

static char	*get_message(char type)
{
	char	*msg;

	msg = NULL;
	if (type == 'f')
		msg = ft_strdup("has taken a fork");
	else if (type == 's')
		msg = ft_strdup("is sleeping");
	else if (type == 'e')
		msg = ft_strdup("is eating");
	else if (type == 't')
		msg = ft_strdup("is thinking");
	else if (type == 'd')
		msg = ft_strdup("died");
	return (msg);
}

static int	log_print(t_log *log)
{
	char	*msg;

	msg = get_message(log->type);
	if (msg == NULL)
	{
		write(2, "get_message:", 12);
		return (1);
	}
	printf("%ld %zd %s\n", log->time, log->philo, msg);
	free(msg);
	return (0);
}

int	log_print_loop(t_log **head_log)
{
	t_log	*lowest;

	if (head_log == NULL)
	{
		write(2, "head_log == NULL\n", 17);
		return (1);
	}
	lowest = NULL;
	while (1)
	{
		lowest = log_search_min(head_log);
		if (lowest != NULL)
		{
			if (log_print(lowest))
				return (1);
			if (lowest->type == 'd')
				return (0);
			if (log_remove(head_log, lowest))
				return (1);
		}
		else
			usleep(10);
		usleep(1);
	}
}
