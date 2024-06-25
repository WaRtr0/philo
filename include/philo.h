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

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_count;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	struct timeval	last_eat;
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_philo			*philo;
}					t_data;

enum	e_status
{
	dead,s
	eat,
	sleep,
	think,
	available,
	taken
};

int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_usleep(int time);

int		is_done(t_data *data, t_philo *philo);
int		get_time(void);
void	print_status(t_philo *philo, char *status);
int		get_fork(t_philo *philo);
int		put_fork(t_philo *philo);
void	*philo_life(void *philo);
void	*death_check(void *philo);
void	*monitor(void *philo);
void	init_philo(t_data *data);
void	free_data(t_data *data);

#endif