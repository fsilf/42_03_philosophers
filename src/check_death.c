/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:46:17 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/07 15:32:25 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //remove
#include <pthread.h>
#include "philo.h"

int	check_death(t_philo_args *philo_args)
{
	if (philo_args->args->end == 1)
	{
		printf("one dead\n");
		return (1);
	}
	return (0);
}
