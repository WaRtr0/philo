/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:01:26 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/23 04:01:28 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	@brief destroy all forks
**  ``src/fork/destroy.c``
**	@param data the data structure
**	@return t_bool TRUE if the forks are destroyed, FALSE otherwise
*/
t_bool	fk_destroys(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (data->forks[i] == NULL || data->forks[i]->is_available == -1)
			break ;
		if (pthread_mutex_destroy(&(data->forks[i]->mutex)))
			return (FALSE);
		free(data->forks[i]);
		i++;
	}
	free(data->forks);
	return (TRUE);
}
