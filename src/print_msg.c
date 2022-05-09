/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:40:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/09 21:24:11 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

static void	ft_putnum(long int num, int fd)
{
	char	c;

	if (num < 10)
	{
		c = num + 48;
		write(fd, &c, fd);
	}
	else
	{
		ft_putnum(num / 10, fd);
		c = (num % 10) + 48;
		write(fd, &c, 1);
	}
}

static void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	num = (long int)n;
	ft_putnum(num, fd);
	write(fd, " ", 1);
}

static void	get_msg(char **msg, char type)
{
	if (type == 'f')
		*msg = ft_strdup("has taken a fork\n");
	if (type == 'e')
		*msg = ft_strdup("is eating\n");
	if (type == 's')
		*msg = ft_strdup("is sleeping\n");
	if (type == 't')
		*msg = ft_strdup("is thinking\n");
	if (type == 'd')
		*msg = ft_strdup("has died\n");
}

void	print_msg(t_philo_args *philo, char type, struct timeval tv_msg)
{
	long unsigned	ms_msg;
	long unsigned	ms_init;
	char			*msg;

	ms_msg = convert_to_milisecs(tv_msg);
	ms_init = convert_to_milisecs(philo->args->tv_init);
	ms_msg = ms_msg - ms_init;
	pthread_mutex_lock(&(philo->args->mutex_print));
	ft_putnbr_fd((int)ms_msg, 1);
	ft_putnbr_fd((int)philo->philo, 1);
	get_msg(&msg, type);
	write(1, msg, ft_strlen(msg));
	pthread_mutex_unlock(&(philo->args->mutex_print));
	free(msg);
}
