/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:52:35 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/14 12:26:31 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args	args;

	ft_memset(&args, -1, sizeof (t_args));
	if (process_argv(argc, argv, &args))
		return (1);
	test_print_args(&args);
	//pthread_create();
	return (0);
}