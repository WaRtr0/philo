/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:15:54 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/19 09:22:48 by mmorot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

/*
**	@brief get id by even or odd
**
**	@param data the data structure
**	@param id the id of the philosopher
**	@param ids the array of ids
**	@return void
*/

static void	must_eat_action(t_philo *philo)
{
	if (philo->data->must_eat_count > 0)
	{
		pthread_mutex_lock(&(philo->eat));
		philo->eat_count++;
		pthread_mutex_unlock(&(philo->eat));
	}
}

static void	get_priority_id(t_data *data, int id, int *ids)
{
	if (id % 2)
	{
		ids[0] = id;
		ids[1] = (id + 1) % data->philo_count;
	}
	else
	{
		ids[0] = (id + 1) % data->philo_count;
		ids[1] = id;
	}
}

void	ph_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	get_priority_id(data, philo->id, philo->priority);
	pthread_mutex_lock(&(data->print));
	pthread_mutex_unlock(&(data->print));
	if (philo->id % 2)
		usleep(data->time_to_eat * 500);
	ph_print_status(philo, thinking);
	while (1)
	{
		if (ph_get_dead(data) || ph_is_dead(philo))
			break ;
		ph_get_forks(data, philo->id);
		ph_print_status(philo, eating);
		philo->last_eat = ft_get_time();
		must_eat_action(philo);
		// if (ph_is_dead(philo) == TRUE)
		// 	break ;
		ph_usleep(data->time_to_eat, philo);
		fk_put(philo->priority[0], data->forks);
		fk_put(philo->priority[1], data->forks);
		ph_print_status(philo, sleeping);
		ph_usleep(data->time_to_sleep, philo);
		ph_print_status(philo, thinking);
		usleep(50);
	}
}
