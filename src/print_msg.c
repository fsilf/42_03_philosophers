/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:40:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/10 15:13:30 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

/*
static void	ft_putnum(unsigned num, int fd)
{
	char	c;

	if (num < 10)
	{
		c = num + 48;
		write(1, &c, 1);
	}
	else
	{
		ft_putnum(num / 10);
		c = (num % 10) + 48;
		write(1, &c, 1);
	}
}

static void	ft_putnbr_fd(unsigned num, int fd)
{
	ft_putnum(num, fd);
	write(fd, " ", 1);
}
*/
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
		*msg = ft_strdup("has died");
}

int	print_msg(t_philo_args *philo, char type)
{
	struct timeval	tv_msg;
	struct timeval	res;
	unsigned		res_ms;
	char			*msg;

	get_msg(&msg, type);
	pthread_mutex_lock(&(philo->args->mutex_print));
	if (philo->args->end == 1)
	{
		pthread_mutex_unlock(&(philo->args->mutex_print));
		return (1);
	}
	gettimeofday(&tv_msg, NULL);
	//ft_timesub_ms(philo->args->tv_init, tv_msg, &res_ms);
	ft_timesub(philo->args->tv_init, tv_msg, &res);
	res_ms = convert_to_milisecs(res);
	if (type == 'd')
		printf("%d %zd %s\n", res_ms, philo->philo, msg);
	else
		printf("%d %zd %s", res_ms, philo->philo, msg);
	pthread_mutex_unlock(&(philo->args->mutex_print));
	/*
	ft_putnbr_fd(convert_to_milisecs(res), fd);
	ft_putnbr_fd(philo->philo, fd);
	write(1, msg, ft_strlen(msg), fd);
	*/
	free(msg);
	return (0);
}
