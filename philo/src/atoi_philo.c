/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:57:05 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 14:39:47 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static ssize_t	ft_atoi_get_number(const char *str, int base, size_t i)
{
	ssize_t	num;

	num = 0;
	while (str[i] >= 48 && str[i] < 58)
	{
		num = num * base;
		num = num + (str[i] - 48);
		i++;
	}
	if (ft_strlen(str) != i)
		return (-1);
	return (num);
}

static ssize_t	ft_strtol(const char *str, int base)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] < 58))
			return (-1);
		return (ft_atoi_get_number(str, base, i));
	}
	return (-1);
}

ssize_t	atoi_philo(const char *str, ssize_t *ptr_num)
{
	*ptr_num = ft_strtol(str, 10);
	if (*ptr_num == -1)
		return (1);
	if (*ptr_num == 0)
		return (1);
	return (0);
}
