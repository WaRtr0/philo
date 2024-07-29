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
t_bool	ph_get_forks(t_philo *philo)
{
	int		put_left;
	int		put_right;

	put_left = 0;
	put_right = 0;
	while (put_left + put_right < 2)
	{
		if (ph_is_dead(philo))
			break ;
		if (!put_left)
			put_left = fk_take(philo, philo->left);
		if (!put_right)
			put_right = fk_take(philo, philo->right);
		usleep(200);
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
	__uint64_t	time;

	time = ft_get_time();
	if (time - philo->last_eat > philo->data->time_to_die)
	{
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
	t_bool	dead;

	pthread_mutex_lock(&data->death);
	dead = data->philo_dead;
	pthread_mutex_unlock(&data->death);
	return (dead);
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
