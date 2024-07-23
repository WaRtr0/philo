/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:00:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/23 04:00:38 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_usleep(int time, t_philo *philo)
{
	suseconds_t	end;
	suseconds_t	actual;

	end = ft_get_time() + time;
	while (1)
	{
		if (ph_is_dead(philo) == TRUE
			|| ph_get_dead(philo->data) == TRUE)
			break ;
		actual = ft_get_time();
		if (actual >= end)
			break ;
		else if (end - actual < 2)
		{
			usleep(1000);
			break ;
		}
		usleep(50);
	}
}
