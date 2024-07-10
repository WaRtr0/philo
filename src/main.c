/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:09:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/11 00:05:01 by mmorot           ###   ########.fr       */
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
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	if (data->philo_count < 1)
		return (ft_putstr_fd(ERR_RULE, 1), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv))
		return (1);
	if (!fk_creates(&data))
		return (1);
	if (!ph_creates(&data))
		return (1);
	ph_start(&data);
	return (0);
}
