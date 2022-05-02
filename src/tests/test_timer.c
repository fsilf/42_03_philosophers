/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_timer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:48:53 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/05/02 14:50:34 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

int	main()
{
	struct timeval	start_time;
	struct timeval	end_time;
	long unsigned	ms_res;
	long unsigned	ms_start;
	long unsigned	ms_end;

	ms_start = 0;
	ms_end = 0;
	ms_res = 0;
	gettimeofday(&start_time, NULL);
	sleep(1);
	usleep(300000);
	gettimeofday(&end_time, NULL);
	printf("start_time:\n");
	test_print_timeval(&start_time);
	printf("end_time:\n");
	test_print_timeval(&end_time);
	ms_start = convert_to_milisecs(&start_time);
	ms_end = convert_to_milisecs(&end_time);
	ms_res = ft_timesub(ms_start, ms_end);
	printf("timesub: start (%ld) - end (%ld): %ld\n", ms_start, ms_end, ms_res);
	ms_res =0;
	ms_res = ft_timesub(ms_end, ms_start);
	printf("timesub: end (%ld) - start (%ld): %ld\n", ms_end, ms_start, ms_res);
	return (0);
}

/*
gcc -Wall -Werror -Wextra -fsanitize=address tests/test_timer.c timer.c ft_memset.c test_prints.c -I../inc/ 
*/
