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

suseconds_t	ft_get_time(void)
{
	struct timeval	time;
	suseconds_t		res;

	gettimeofday(&time, (void *)0);
	res = time.tv_sec;
	res *= 1000000;
	res += time.tv_usec;
	return (res);
}
