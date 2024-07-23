/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:01:04 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/23 04:01:06 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (ft_putstr_fd(ERR_NBR, 2), 0);
		i++;
	}
	if (i > 9)
		return (ft_putstr_fd(ERR_BIG, 2), 0);
	if (i == 0)
		return (ft_putstr_fd(ERR_ARG, 2), 0);
	return (1);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERR_ARG, 1), 1);
	i = 0;
	while (argv[++i])
		if (!is_number(argv[i]))
			return (1);
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = 0;
	pthread_mutex_init(&(data->death), NULL);
	pthread_mutex_init(&(data->print), NULL);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	if (data->philo_count < 1)
		return (ft_putstr_fd(ERR_RULE, 1), 1);
	if (data->philo_count > 250)
		return (ft_putstr_fd(ERR_NB_PHILO, 1), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv))
		return (1);
	if (!fk_creates(&data))
		return (fk_destroys(&data));
	pthread_mutex_lock(&(data.print));
	if (ph_creates(&data))
	{
		ph_set_dead(&data, TRUE);
		pthread_mutex_unlock(&(data.print));
		ph_join(&data);
		fk_destroys(&data);
		return (ph_destroys(&data), 1);
	}
	ph_set_dead(&data, FALSE);
	data.start_time = ft_get_time();
	pthread_mutex_unlock(&(data.print));
	ph_join(&data);
	if (data.must_eat_count > 0)
		pthread_join(data.manager, NULL);
	ph_destroys(&data);
	fk_destroys(&data);
	return (0);
}
