/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:00:36 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/27 12:33:56 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ph_usleep(int time, t_philo *philo)
// {
// 	suseconds_t	end;
// 	suseconds_t	actual;

// 	end = ft_get_time() + time;
// 	while (1)
// 	{
// 		// if (ph_is_dead(philo) == TRUE
// 		// 	|| ph_get_dead(philo->data) == TRUE)
// 		// 	break ;
// 		if (ph_is_dead(philo) == TRUE)
// 			break ;
// 		actual = ft_get_time();
// 		if (actual >= end)
// 			break ;
// 		else if (end - actual < 2)
// 		{
// 			usleep(1000);
// 			break ;
// 		}
// 		usleep(50);
// 	}
// }

suseconds_t get_end(t_philo *philo, int time)
{
	suseconds_t	end_default;
	suseconds_t	actual;
	suseconds_t	end_dead;
	suseconds_t	end_no_time;

	actual = ft_get_time();
	end_default = actual + time;
	end_dead = actual + philo->data->time_to_die;
	end_no_time = philo->last_eat + philo->data->time_to_die;
	if (end_dead < end_default && end_dead < end_no_time)
		return (end_dead - actual);
	if (end_no_time < end_default && end_no_time < end_dead)
		return (end_no_time - actual);
	return (end_default - actual);
}

void	ph_usleep(int time, t_philo *philo)
{
	suseconds_t	end;

	end = get_end(philo, time);
	usleep(end);
	// ph_get_dead(philo->data);
	ph_is_dead(philo);
}