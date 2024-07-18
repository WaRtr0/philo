/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:45:49 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/18 18:19:30 by mmorot           ###   ########.fr       */
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

/*
**	@brief get forks
**  ``src/philo/life.c``
**	@param data the data structure
**	@param id the id of the philosopher
**	@return t_bool TRUE if the forks are taken, FALSE otherwise
*/
t_bool	ph_get_forks(t_data *data, int id)
{
	int	fork_count;
	int	ids[2];

	fork_count = 0;
	get_priority_id(data, id, ids);
	while (fork_count < 2)
	{
		if (fk_take(ids[0], data->forks))
			fork_count++;
		if (fork_count)
		{
			ph_print_status(data->philo[id], taking);
			if (fk_take(ids[1], data->forks))
				fork_count++;
			else
			{
				fk_put(ids[0], data->forks);
				fork_count = 0;
			}
		}
	}
	ph_print_status(data->philo[id], taking);
	return (TRUE);
}

/*
** @brief check if the philosopher is dead
**  ``src/philo/manipulate.c``
** @param philo the philosopher
** @return t_bool TRUE if the philosopher is dead, FALSE otherwise
*/
t_bool	ph_is_dead(t_philo *philo)
{
	suseconds_t	time;

	time = ft_get_time();
	if (time - philo->last_eat > philo->data->time_to_die)
	{
		ph_set_dead(philo->data);
		ph_print_status(philo, dead);
		return (TRUE);
	}
	return (FALSE);
}

/*
** @brief get the dead status
**  ``src/philo/manipulate.c``
** @param data the data structure
** @return t_bool TRUE if the philosopher is dead, FALSE otherwise
*/
t_bool	ph_get_dead(t_data *data)
{
	pthread_mutex_lock(&data->death);
	if (data->philo_dead == TRUE)
	{
		pthread_mutex_unlock(&data->death);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->death);
	return (FALSE);
}

/*
** @brief set the dead status
**  ``src/philo/manipulate.c``
** @param data the data structure
** @return ``void``
*/
void	ph_set_dead(t_data *data)
{
	pthread_mutex_lock(&data->death);
	data->philo_dead = TRUE;
	pthread_mutex_unlock(&data->death);
}
