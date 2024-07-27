/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:02:33 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/27 12:39:40 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	@brief get forks
**  ``src/philo/life.c``
**	@param data the data structure
**	@param id the id of the philosopher
**	@return t_bool TRUE if the forks are taken, FALSE otherwise
*/
// t_bool	ph_get_forks(t_data *data, int id)
// {
// 	int		take[2];
// 	t_philo	*philo;

// 	philo = data->philo[id];
// 	take[0] = 0;
// 	take[1] = 0;
// 	if ()
// 	if (!take[0] && fk_take(philo->priority[0], data->forks))
// 	{
// 		ph_print_status(philo, taking);
// 		take[0]++;
// 	}
// 	if (take[0] && !take[1] && fk_take(philo->priority[1], data->forks))
// 	{
// 		ph_print_status(philo, taking);
// 		take[1]++;
// 	}
// 	ph_is_dead(philo);
// 	return (TRUE);
// }
t_bool	ph_get_forks(t_data *data, int id)
{
	int		take[2];
	t_philo	*philo;

	philo = data->philo[id];
	take[0] = 0;
	take[1] = 0;
	while (take[0] + take[1] < 2)
	{
		if (ph_is_dead(philo))
			break ;
		if (!take[0] && fk_take(philo->priority[0], data->forks))
		{
			ph_print_status(philo, taking);
			take[0]++;
		}
		if (take[0] && !take[1] && fk_take(philo->priority[1], data->forks))
		{
			ph_print_status(philo, taking);
			take[1]++;
		}
		usleep(250);
	}
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
		ph_print_status(philo, dead);
		ph_set_dead(philo->data, TRUE);
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
void	ph_set_dead(t_data *data, t_bool value)
{
	pthread_mutex_lock(&data->death);
	data->philo_dead = value;
	pthread_mutex_unlock(&data->death);
}
