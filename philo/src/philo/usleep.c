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

static inline __uint64_t	get_end(t_philo *philo, __uint64_t time)
{
	__uint64_t	end_default;
	__uint64_t	actual;
	__uint64_t	end_dead;
	__uint64_t	end_no_time;

	actual = ft_get_time();
	end_default = actual + time;
	end_dead = actual + philo->data->time_to_die;
	end_no_time = philo->last_eat + philo->data->time_to_die;
	if (end_dead < end_default && end_dead <= end_no_time)
		return (end_dead + 1);
	if (end_no_time < end_default && end_no_time <= end_dead)
		return (end_no_time + 1);
	return (end_default);
}

inline void	ph_usleep(__uint64_t time, t_philo *philo)
{
	__uint64_t	end;

	end = get_end(philo, time);
	while (ft_get_time() < end)
		usleep(100);
	ph_is_dead(philo);
}
