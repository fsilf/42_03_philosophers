/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_loops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:50:25 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/13 13:21:43 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	add_num_loops(t_philo_args *philo)
{
	if (philo->args->num_loops == 0)
		return (0);
	philo->counter = philo->counter + 1;
	if (philo->counter >= philo->args->num_loops)
		sem_post(philo->sem_counter);
	return (0);
}
