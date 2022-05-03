/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:29:11 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/03 11:23:41 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

t_log	*log_new(long unsigned time, char type, ssize_t philo)
{
	t_log	*log_elem;

	log_elem = NULL;
	log_elem = (t_log *)malloc(sizeof (t_log));
	if (log_elem == NULL)
	{
		perror("log_new: malloc:");
		return (NULL);
	}
	ft_memset(log_elem, 0, sizeof(t_log));
	log_elem->type = type;
	log_elem->time = time;
	log_elem->philo = philo;
	log_elem->next = NULL;
	log_elem->prev = NULL;
	log_elem->num = -1;
	return (log_elem);
}

void	log_addback(t_log **head_log, t_log *new_log, \
						pthread_mutex_t *mutex_queue)
{
	t_log	*last;

	if (head_log == NULL)
		return ;
	//gestionar exits
	pthread_mutex_lock(mutex_queue);
	last = log_last(*head_log);
	if (last != NULL)
	{
		new_log->num = last->num + 1;
		last->next = new_log;
		new_log->prev = last;
	}
	else
	{
		new_log->num = 1;
		*head_log = new_log;
	}
	pthread_mutex_unlock(mutex_queue);
	return ;
	//gestionar exits
}

t_log	*log_last(t_log *head_log)
{
	t_log	*temp;
	t_log	*last;

	temp = head_log;
	last = NULL;
	while (temp)
	{
		last = temp;
		temp = temp->next;
	}
	return (last);
}

int	log_remove(t_log **head_log, t_log *to_remove)
{
	t_log	*temp;

	if (head_log == NULL || *head_log == NULL || to_remove == NULL)
		return (1);
	if (to_remove->num == -1)
		return (1);
	temp = *head_log;
	while (temp != NULL)
	{
		if (temp->num == to_remove->num)
		{
			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			else
				*head_log = temp->next;
			if (temp->next != NULL)
				temp->next->prev = temp->prev;
			free(temp);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	log_free_all(t_log **head_log)
{
	t_log	*temp;
	t_log	*curr;

	if (head_log == NULL || *head_log == NULL)
		return (0);
	curr = *head_log;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(head_log);
	return (0);
}
