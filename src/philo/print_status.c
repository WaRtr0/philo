/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:02:52 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/27 12:47:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	ph_print_status(t_philo *philo, t_state state)
{
	suseconds_t	time;
	static char	*message[] = {
		"died\n",
		"is eating\n",
		" is sleeping\n",
		"is thinking\n",
		"has taken a fork\n"
	};

	time = ft_get_time();
	if (state == eating)
		philo->last_eat = time;
	pthread_mutex_lock(&(philo->data->death));
	if ((state == dead && philo->data->philo_dead == FALSE)
		|| philo->data->philo_dead == FALSE)
		printf("%zu %u %s", (time - philo->data->start_time) / 1000,
			philo->id + 1, message[state]);
	if (state == dead)
		philo->data->philo_dead = TRUE;
	pthread_mutex_unlock(&(philo->data->death));
}
