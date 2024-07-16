/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:15:54 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/16 02:32:31 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->print));
	pthread_mutex_unlock(&(data->print));
	printf("philo %p\n", philo->data);
	if (philo->id % 2)
		ph_usleep(100, philo);
	// printf("C\n");
	// sleep(100000000);

	while (1)
	{
		if (ph_get_dead(data) || ph_is_dead(philo))
			break ;
		ph_get_forks(data, philo->id);
		philo->last_eat = ft_get_time();
		ph_usleep(data->time_to_eat, philo);
		fk_put(philo->id, data->forks);
		fk_put((philo->id + 1) % data->philo_count, data->forks);
		ph_print_status(philo, sleeping);
		ph_usleep(data->time_to_sleep, philo);
		ph_print_status(philo, thinking);
	}
}
