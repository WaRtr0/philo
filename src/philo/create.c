/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:02:17 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/23 04:02:18 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	add_manager(t_data *data)
{
	if (data->must_eat_count > 0 && pthread_create(&(data->manager),
			NULL, (void *)manager, data))
		return (1);
	return (0);
}

static void	get_priority_id(t_data *data, t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->left = data->forks[philo->id];
		philo->right = data->forks[(philo->id + 1) % data->philo_count];
	}
	else
	{
		philo->left = data->forks[(philo->id + 1) % data->philo_count];
		philo->right = data->forks[philo->id];
	}
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
		data->philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!data->philo[i])
			return (1);
		data->philo[i]->id = i;
		data->philo[i]->last_eat = ft_get_time();
		get_priority_id(data, data->philo[i]);
		pthread_mutex_init(&(data->philo[i]->eat), NULL);
		data->philo[i]->data = data;
		if (pthread_create(&(data->philo[i]->thread), NULL,
				(void *)ph_routine, data->philo[i]))
			return (1);
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
		if (data->philo[i] == NULL || data->philo[i]->thread == 0)
			break ;
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
		if (data->philo[i] == NULL)
			break ;
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
}
