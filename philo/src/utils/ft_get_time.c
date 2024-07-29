/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:59:55 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/23 03:59:57 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

__uint64_t	ft_get_time(void)
{
	struct timeval	time;
	__uint64_t		res;

	gettimeofday(&time, (void *)0);
	res = (__uint64_t)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (res);
}
