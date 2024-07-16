/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:18:19 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/11 00:13:25 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (end > time - 50)
			usleep(end);
		else
			usleep(100);
		if (end > time)
			break ;
	}
}
