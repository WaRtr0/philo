/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:18:19 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/19 09:23:29 by mmorot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	ph_usleep(int time, t_philo *philo)
{
	suseconds_t	start;
	suseconds_t	end;

	start = ft_get_time();
	while (1)
	{
		end = ft_get_time() - start;
		if (ph_get_dead(philo->data) == TRUE
			|| ph_is_dead(philo) == TRUE)
			break ;
		usleep(50);
		if (end >= time)
			break ;
	}
}
