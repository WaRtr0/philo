/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:03:12 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/27 12:37:58 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	must_eat_action(t_philo *philo)
{
	if (philo->data->must_eat_count > 0)
	{
		pthread_mutex_lock(&(philo->eat));
		philo->eat_count++;
		pthread_mutex_unlock(&(philo->eat));
	}
}

void	ph_routine(t_philo *philo)
{
	t_data				*data;
	const __uint64_t	time_to_sleep = philo->data->time_to_sleep;
	const __uint64_t	time_to_eat = philo->data->time_to_eat;

	data = philo->data;
	pthread_mutex_lock(&(data->death));
	pthread_mutex_unlock(&(data->death));
	philo->last_eat = data->start_time;
	if (philo->id % 2)
		ph_usleep(time_to_eat / 2, philo);
	while (!(ph_is_dead(philo) || ph_get_dead(data)))
	{
		ph_get_forks(philo);
		ph_print_status(philo, eating);
		ph_usleep(data->time_to_eat, philo);
		must_eat_action(philo);
		fk_puts(philo);
		ph_print_status(philo, sleeping);
		ph_usleep(time_to_sleep, philo);
		ph_print_status(philo, thinking);
		usleep(100);
	}
	fk_puts(philo);
}
