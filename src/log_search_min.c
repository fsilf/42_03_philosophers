/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_search_min.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:12:04 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/02 17:52:17 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_log	*log_search_min(t_log **head_log)
{
	t_log	*temp;
	t_log	*lowest;

	if (head_log == NULL || *head_log == NULL)
		return (NULL);
	lowest = *head_log;
	temp = *head_log;
	while (temp != NULL)
	{
		if (lowest->time > temp->time)
			lowest = temp;
		temp = temp->next;
	}
	return (lowest);
}
