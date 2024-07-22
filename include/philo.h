/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:16:29 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/22 05:23:44 by mmorot           ###   ########.fr       */
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

typedef char	t_bool;
# define TRUE 1
# define FALSE 0

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
	int				philo_count; /** number of philo  ``arg[1]``*/
	suseconds_t		start_time; /** start time*/
	int				time_to_die; /** time to die ``arg[2]``*/
	int				time_to_eat; /** time to eat ``arg[3]``*/
	int				time_to_sleep; /** time to sleep ``arg[4]``*/
	int				must_eat_count; /** must eat count ``?arg[5]``*/
	t_bool			philo_dead; /** check if dead*/
	t_fork			**forks; /** is a array on fork struct*/
	pthread_mutex_t	print; /** print mutex for  ``ph_print_status``*/
	pthread_mutex_t	death; /** death mutex for  ``philo_dead``*/
	pthread_t		manager;
	struct s_philo	**philo; /** is a array on philo struct*/
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
	int				id; /** id of philo*/
	t_data			*data; /** pointer on global data [/data/philo == ../] */
	pthread_t		thread; /** thread of philo */
	int				priority[2];	/** id priority*/
	int				eat_count; /** eat_count of philo*/
	pthread_mutex_t	eat;
	suseconds_t		last_eat; /** last_eat of philo*/
}	t_philo; /** philo structure*/

int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		*ft_calloc(size_t count, size_t size);
suseconds_t	ft_get_time(void);

t_bool		fk_creates(t_data *data);
t_bool		fk_destroys(t_data *data);
t_bool		fk_take(int id, t_fork **forks);
t_bool		fk_put(int id, t_fork **forks);

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