/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-f <fsilva-f@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:15:27 by fsilva-f          #+#    #+#             */
/*   Updated: 2022/03/14 12:35:49 by fsilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	c_c;
	size_t			i;
	char			*ptr;

	c_c = (unsigned char)c;
	i = 0;
	ptr = (char *)str;
	while (i < len)
	{
		ptr[i] = c_c;
		i++;
	}
	return ((void *) ptr);
}
