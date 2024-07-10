/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:47:28 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/10 19:56:19 by mmorot           ###   ########.fr       */
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
		if (pthread_mutex_destroy(&(data->forks[i]->mutex)))
			return (FALSE);
		free(data->forks[i]);
		i++;
	}
	free(data->forks);
	return (TRUE);
}
