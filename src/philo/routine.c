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
	if ((ph_get_dead(data)))
		return ;
	get_priority_id(data, philo->id, philo->priority);
	pthread_mutex_lock(&(data->print));
	usleep(100);
	pthread_mutex_unlock(&(data->print));
	philo->last_eat = data->start_time;
	if (philo->id != philo->priority[0])
		usleep(data->time_to_eat * 1000);
	while (!(ph_get_dead(data) || ph_is_dead(philo)))
	{
		ph_get_forks(data, philo->id);
		ph_print_status(philo, eating);
		philo->last_eat = ft_get_time();
		ph_usleep(data->time_to_eat, philo);
		must_eat_action(philo);
		fk_put(philo->priority[0], data->forks);
		fk_put(philo->priority[1], data->forks);
		ph_print_status(philo, sleeping);
		ph_usleep(data->time_to_sleep, philo);
		ph_print_status(philo, thinking);
	}
}
