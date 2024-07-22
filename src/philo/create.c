/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:20:18 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/22 05:26:21 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	add_manager(t_data *data)
{
	if (data->must_eat_count > 0)
	{
		if (pthread_create(&(data->manager), NULL, (void *)manager, data))
			return (1);
	}
	return (0);
}

/*
**   @brief create all philo
**   ``src/philo/create.c``
**   @param data the data structure
**   @return int 1 if an error occured, 0 otherwise
*/
int	ph_creates(t_data *data)
{
	int		i;

	i = 0;
	data->philo = ft_calloc(data->philo_count, sizeof(t_philo *));
	if (!data->philo)
		return (1);
	while (i < data->philo_count)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (1);
		data->philo[i]->id = i;
		data->philo[i]->last_eat = ft_get_time();
		pthread_mutex_init(&(data->philo[i]->eat), NULL);
		data->philo[i]->data = data;
		if (pthread_create(&(data->philo[i]->thread), NULL,
				(void *)ph_routine, data->philo[i]))
		{
			//destroy all
			return (1);
		}
		i++;
	}
	return (add_manager(data));
}

void	ph_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
}

void	ph_destroys(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
	// return (0);
}
