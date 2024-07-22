/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:16:16 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/22 05:20:13 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_count(t_philo **philo, int nbs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < nbs)
	{
		pthread_mutex_lock(&(philo[i]->eat));
		if (philo[i]->eat_count >= philo[i]->data->must_eat_count)
			count++;
		pthread_mutex_unlock(&(philo[i]->eat));
		i++;
	}
	if (nbs == count)
		return (1);
	return (0);
}

void	manager(t_data *data)
{
	pthread_mutex_lock(&(data->print));
	pthread_mutex_unlock(&(data->print));
	while (1)
	{
		if (ph_get_dead(data))
			break ;
		if (get_count(data->philo, data->philo_count))
			ph_set_dead(data, TRUE);
		usleep(data->time_to_eat * 500);
	}
}
