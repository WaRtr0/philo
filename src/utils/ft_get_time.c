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

/*
**    @brief get the current time in milliseconds
**    ``src/utils/ft_get_time.c``
**    @return ``__suseconds_t`` | ``long int`` the current time in milliseconds
*/
suseconds_t	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, (void *)0);
	return ((long)(time.tv_sec) *1000 + (time.tv_usec / 1000));
}
