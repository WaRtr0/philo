/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:35:39 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/10 20:04:16 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	@brief check if the fork is available
**  ``src/fork/manipulate.c``
**  @warning the fork must be locked before calling this function
**	@param forks the forks array
**	@param id the id of the fork
**	@return t_bool TRUE if the fork is available, FALSE otherwise
*/
static	t_bool	is_available(t_fork **forks, int id)
{
	if (forks[id]->is_available == TRUE)
		return (TRUE);
	return (FALSE);
}

/*
**	@brief set the state of the fork
**  ``src/fork/manipulate.c``
**  @warning the fork must be locked before calling this function
**	@param forks the forks array
**	@param id the id of the fork
**	@param state the state to set
**	@return t_bool TRUE if the state is set, FALSE otherwise
*/
static	t_bool	set_state(t_fork **forks, int id, t_bool state)
{
	if (state == TRUE)
		forks[id]->is_available = TRUE;
	else
		forks[id]->is_available = FALSE;
	return (forks[id]->is_available);
}

/*
**	@brief put the fork
**  ``src/fork/manipulate.c``
**  @param id the id of the philosopher
**	@param data the data structure
**	@return t_bool TRUE if the fork is put, FALSE otherwise
**  @note pthread_mutex_trylock is better than pthread_mutex_lock...
*/
t_bool	fk_put(int id, t_fork **forks)
{
	if (!pthread_mutex_lock(&(forks[id]->mutex)))
	{
		set_state(forks, id, TRUE);
		pthread_mutex_unlock(&(forks[id]->mutex));
		return (TRUE);
	}
	return (FALSE);
}


/*
**	@brief take the fork
**  ``src/fork/manipulate.c``
**  @param id the id of the philosopher
**	@param data the data structure
**	@return t_bool TRUE if the fork is taken, FALSE otherwise
**  @note pthread_mutex_trylock is better than pthread_mutex_lock...
*/
t_bool	fk_take(int id, t_fork **forks)
{
	if (!pthread_mutex_lock(&(forks[id]->mutex)))
	{
		if (is_available(forks, id) == TRUE)
		{
			set_state(forks, id, FALSE);
			pthread_mutex_unlock(&(forks[id]->mutex));
			return (TRUE);
		}
		pthread_mutex_unlock(&(forks[id]->mutex));
		return (FALSE);
	}
	return (FALSE);
}

/*
**	@brief create all forks
**  ``src/fork/manipulate.c``
**	@param id the id of the philosopher
**	@param data the data structure
**	@return t_bool TRUE if the fork is put, FALSE otherwise
*/
t_bool	fk_creates(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork *) * data->philo_count);
	if (!data->forks)
		return (FALSE);
	while (i < data->philo_count)
	{
		data->forks[i] = malloc(sizeof(t_fork));
		if (!data->forks[i])
			return (FALSE);
		set_state(data->forks, i, TRUE);
		if (pthread_mutex_init(&(data->forks[i]->mutex), NULL))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
