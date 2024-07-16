/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:16:29 by mmorot            #+#    #+#             */
/*   Updated: 2024/07/16 02:37:39 by mmorot           ###   ########.fr       */
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


typedef enum e_state
{
	dead,
	eating,
	sleeping,
	thinking,
	taking
}	t_state;

typedef struct fork
{
	t_bool			is_available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data
{
	int				philo_count;
	suseconds_t		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	t_bool			philo_dead;
	t_fork			**forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	struct s_philo	**philo;
}					t_data;
typedef struct s_philo
{
	int				id;
	t_data			*data;
	pthread_t		thread;
	int				eat_count;
	t_state			state;
	suseconds_t		last_eat;
}					t_philo;

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
void		ph_set_dead(t_data *data);
t_bool		ph_is_dead(t_philo *philo);


void		ph_routine(t_philo *philo);
void		ph_print_status(t_philo *philo, t_state state);

#endif