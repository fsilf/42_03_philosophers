/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 13:12:00 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/08 14:41:19 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args			args;

	if (process_argv(argc, argv, &args))
		return (1);
	test_print_args(args);
	cleanup_forks(args.forks, args.mutex_fork, args.num_philo);
	return (0);
}
