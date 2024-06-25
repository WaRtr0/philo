/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:45:49 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/25 16:18:22 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://github.com/ma-gabriel/philo/blob/main/srcs/philo.c

# include "philo.h"

static int	is_dead(t_data *data, t_philo *philo)
{
    int	time;
    time = get_time();
    if (time - philo->last_eat.tv_sec > data->time_to_die)
    {
        print_status(philo, DEAD);
        pthread_mutex_unlock(philo->death);
        return (1);
    }
    return (0);
}


int get_fork(t_data *data, int id)
{
    int is_take;

    is_take = 0;
    if (!pthread_mutex_lock(&(data->forks[id]->mutex)))
    {
        if (data->forks[id]->status == available)
        {
            data->forks[id]->status = taken;
            is_take = 1;
        }
        pthread_mutex_unlock(&(data->forks[id]->mutex));
    }
    return (is_take);
}

int get_forks(t_data *data, int id)
{
    if (id % 2)
    {
        while (t
        pthread_mutex_lock();
        pthread_mutex_lock(philo->left_fork);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    return (0);
}

int		routine(t_data *data, t_philo *philo)
{
    if (philo->id % 2)
        ft_usleep(50);
    while (1)
    {
        if (is_dead(data, philo))
            return (1);
        if ()
        get_fork(philo);
        print_status(philo, EAT);
        philo->last_eat.tv_sec = get_time();
        ft_usleep(data->time_to_eat);
        put_fork(philo);
        print_status(philo, SLEEP);
        ft_usleep(data->time_to_sleep);
        print_status(philo, THINK);
    }
}