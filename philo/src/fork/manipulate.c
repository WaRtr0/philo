/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:01:45 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/23 04:01:47 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	@brief put the fork
**  ``src/fork/manipulate.c``
**  @param id the id of the philosopher
**	@param data the data structure
**	@return t_bool TRUE if the fork is put, FALSE otherwise
**  @note pthread_mutex_trylock is better than pthread_mutex_lock...
*/
t_bool	fk_puts(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left->mutex));
	philo->left->is_available = TRUE;
	pthread_mutex_unlock(&(philo->left->mutex));
	pthread_mutex_lock(&(philo->right->mutex));
	philo->right->is_available = TRUE;
	pthread_mutex_unlock(&(philo->right->mutex));
	return (TRUE);
}

/*
**	@brief take the fork
**  ``src/fork/manipulate.c``
**  @param id the id of the philosopher
**	@param data the data structure
**	@return t_bool TRUE if the fork is taken, FALSE otherwise
**  @note pthread_mutex_trylock is better than pthread_mutex_lock...
*/
t_bool	fk_take(t_philo *philo, t_fork *fork)
{
	t_bool	available;

	pthread_mutex_lock(&(fork->mutex));
	available = fork->is_available;
	fork->is_available = FALSE;
	pthread_mutex_unlock(&(fork->mutex));
	if (available)
		ph_print_status(philo, taking);
	return (available);
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
	data->forks = ft_calloc(data->philo_count, sizeof(t_fork *));
	if (!data->forks)
		return (FALSE);
	while (i < data->philo_count)
	{
		data->forks[i] = ft_calloc(1, sizeof(t_fork));
		if (!data->forks[i])
			return (FALSE);
		data->forks[i]->is_available = TRUE;
		if (pthread_mutex_init(&(data->forks[i]->mutex), NULL))
		{
			data->forks[i]->is_available = -1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
