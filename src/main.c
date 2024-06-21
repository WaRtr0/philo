/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:09:21 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/19 18:23:40 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Function to initialize the data structure
* @param data: the data structure
* @param argc: the number of arguments 4 ?5
* @param argv: the arguments
* number_of_philosophers [INT] (2 <= number_of_philosophers <= 200)
* time_to_die [INT(ms)] (60 <= time_to_die <= 1000)
* time_to_eat [INT(ms)]
* time_to_sleep [INT(ms)]
* ? number_of_times_each_philosopher_must_eat [INT]
* @return: int 0 if success, 1 if error
*/

int	init_data(t_data *data, int	argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("ffjjffgjjddndkdqwjdwjdjdjdkjnkjfefwehfejfjhfjfse\n", 1);
		return (1);
	}
	ft_putstr_fd("Tout es yep tout est bgiwdeioefkfeif feiufweiifweio ok\n", 1);
	(void)data;
	(void)argv;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		ft_putstr_fd("\n", 1);
		argv++;
	}
	if (init_data(&data, argc, argv))
		return (1);
	printf("salut toutdnde\n");
	return (0);
}
