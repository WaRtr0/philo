/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:47:28 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/22 23:16:24 by mmorot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
