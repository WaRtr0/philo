/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:03:43 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/27 12:48:32 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define P_FORK		"has taken a fork"
# define P_EAT		"is eating"
# define P_SLEEP		"is sleeping"
# define P_THINK		"is thinking"
# define P_DEAD		"died"

# define ERR_ARG	"Error: Invalid arguments count\n"
# define ERR_MALLOC	"Error: Malloc failed\n"
# define ERR_THREAD	"Error: Thread creation failed\n"
# define ERR_MUTEX	"Error: Mutex creation failed\n"
# define ERR_NBR	"Error: Is not numeric\n"
# define ERR_BIG	"Error: Big Number\n"
# define ERR_RULE	"Error: Rule not respected\n"
# define ERR_NB_PHILO "Error: Max philo is 250\n"
# define TRUE 1
# define FALSE 0

typedef char	t_bool;

/**
 * @brief state enum for ``ph_print_status``
 * @param dead philo is dead
 * @param eating philo is eating
 * @param sleeping philo is sleeping
 * @param thinking philo is thinking
 * @param taking philo is taking a fork
 */
typedef enum e_state
{
	dead,
	eating,
	sleeping,
	thinking,
	taking
}	t_state;

/**
 * @brief fork struct
 * @param is_available check if the fork is available
 * @param mutex mutex for the fork
 */
typedef struct fork
{
	t_bool			is_available;
	pthread_mutex_t	mutex;
}	t_fork;

/**
 * @brief data struct
 * @param philo_count number of philo  ``arg[1]``
 * @param start_time start time of global data
 * @param time_to_die time to die ``arg[2]``
 * @param time_to_eat time to eat ``arg[3]``
 * @param time_to_sleep time to sleep ``arg[4]``
 * @param must_eat_count must eat count ``?arg[5]``
 * @param philo_dead check if dead
 * @param forks is a array on fork struct
 * @param print print mutex for  ``ph_print_status``
 * @param death death mutex for  ``philo_dead``
 * @param philo is a array on philo struct
 */
typedef struct s_data
{
	int				philo_count;
	suseconds_t		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	//tfreydie test
	// int				is_dinner_started;

	t_bool			philo_dead;
	t_fork			**forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		manager;
	struct s_philo	**philo;
}					t_data;

/** @struct struct s_philo
 *  @brief philo struct
 *  @param id id of philo
 *  @param data pointer on global data [/data/philo == ../]
 *  @param thread thread of philo
 *  @param priority	id priority
 *  @param eat_count eat_count of philo
 *  @param last_eat last_eat of philo
*/
typedef struct s_philo
{
	int				id;
	t_data			*data;
	pthread_t		thread;
	int				priority[2];
	int				eat_count;
	pthread_mutex_t	eat;
	suseconds_t		last_eat;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_putstr_len_fd(char *s, int len, int fd);
void		ft_putnbr_fd(int n, int fd);
void		*ft_calloc(size_t count, size_t size);
suseconds_t	ft_get_time(void);

t_bool		fk_creates(t_data *data);
t_bool		fk_destroys(t_data *data);
t_bool		fk_take(t_philo *philo, t_fork *fork);
t_bool		fk_put(t_fork *fork);

int			ph_creates(t_data *data);
void		ph_join(t_data *data);
void		ph_destroys(t_data *data);
void		ph_usleep(int time, t_philo *philo);
t_bool		ph_get_forks(t_data *data, int id);

t_bool		ph_get_dead(t_data *data);
void		ph_set_dead(t_data *data, t_bool value);
t_bool		ph_is_dead(t_philo *philo);

void		ph_routine(t_philo *philo);
void		ph_print_status(t_philo *philo, t_state state);

void		manager(t_data *data);
#endif
