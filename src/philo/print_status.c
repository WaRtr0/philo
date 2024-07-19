/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:17:14 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/18 19:10:40 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	@brief print the status of the philosopher
**  ``src/philo/print_status.c``
**	@param philo the philosopher pointer
**	@param state the state to print
*/
void	ph_print_status(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&(philo->data->print));
	if (state == dead || ph_get_dead(philo->data) == FALSE)
	{
		ft_putnbr_fd(ft_get_time() - philo->data->start_time, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id + 1, 1);
		if (state == dead)
			ft_putstr_fd(" died\n", 1);
		else if (state == eating)
			ft_putstr_fd(" is eating\n", 1);
		else if (state == sleeping)
			ft_putstr_fd(" is sleeping\n", 1);
		else if (state == thinking)
			ft_putstr_fd(" is thinking\n", 1);
		else if (state == taking)
			ft_putstr_fd(" has taken a fork\n", 1);
	}
	pthread_mutex_unlock(&philo->data->print);
}
