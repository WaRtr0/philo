/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:02:52 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/27 12:47:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	@brief print the status of the philosopher
**  ``src/philo/print_status.c``
**	@param philo the philosopher pointer
**	@param state the state to print
*/
// # define DIED " died\n"
// void	ph_print_status(t_philo *philo, t_state state)
// {
// 	t_bool philo_dead = ph_get_dead(philo->data);
// 	pthread_mutex_lock(&(philo->data->print));
// 	// pthread_mutex_lock(&(philo->data->death));
// 	if ((state == dead && philo_dead == FALSE)
// 		|| philo_dead == FALSE)
// 	{
// 		pthread_mutex_unlock(&(philo->data->death));
// 		ft_putnbr_fd((ft_get_time() - philo->data->start_time) / 1000, 1);
// 		ft_putstr_len_fd(" ", 1, 1);
// 		ft_putnbr_fd(philo->id + 1, 1);
// 		if (state == dead)
// 			ft_putstr_len_fd(DIED, sizeof(DIED), 1);
// 		else if (state == eating)
// 			ft_putstr_len_fd(" is eating\n", 11, 1);
// 		else if (state == sleeping)
// 			ft_putstr_len_fd(" is sleeping\n", 13, 1);
// 		else if (state == thinking)
// 			ft_putstr_len_fd(" is thinking\n", 13, 1);
// 		else if (state == taking)
// 			ft_putstr_len_fd(" has taken a fork\n", 18, 1);
// 	}
// 	// else
// 		// pthread_mutex_unlock(&(philo->data->death));
// 	pthread_mutex_unlock(&philo->data->print);
// }



void	ph_print_status(t_philo *philo, t_state state)
{
	static char *message[] = {
		"died\n",
		"is eating\n",
		" is sleeping\n",
		"is thinking\n",
		"has taken a fork\n"
	};
	pthread_mutex_lock(&(philo->data->print));
	pthread_mutex_lock(&(philo->data->death));
	if ((state == dead && philo->data->philo_dead == FALSE)
		|| philo->data->philo_dead == FALSE)
	{
		pthread_mutex_unlock(&(philo->data->death));
		printf("%ld %d %s", (ft_get_time() - philo->data->start_time) / 1000,  philo->id + 1, message[state]);
	}
	else
		pthread_mutex_unlock(&(philo->data->death));
	pthread_mutex_unlock(&philo->data->print);
}


