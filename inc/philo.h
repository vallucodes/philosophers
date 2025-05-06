/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:39:19 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/05 15:28:58 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> //NULL
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <pthread.h> //threads
# include <unistd.h> //usleep, write
# include <errno.h> //errno
# include <stdbool.h> //bool
# include <stdint.h> //SIZE_MAX

# define ARGS1		"Incorrect amount of arguments\nUsage: ./philo [number_of_"
# define ARGS2		"philosophers] [time_to_die] [time_to_eat] [time_to_sleep] "
# define ARGS3		"([number_of_times_each_philosopher_must_eat])\n"
# define MALLOC		"Error: malloc failure\n"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define FORK		"has taken a fork"
# define DEATH		"died"

# define INPUT		"Error: input not valid, must be numeric\n"
# define AMOUNT		"Error: amount of philosophers must be between 1 and 1000\n"
# define TIME_TO_DIE	"Error: time to die must be greater than 0\n"
# define TIME_TO_EAT	"Error: time to eat must be greater than 0\n"
# define TIME_TO_SLEEP	"Error: time to sleep must be greater than 0\n"
# define MEALS			"Error: amount of meals must be greater than 0\n"
# define OVERFLOW		"Error: One of the values is too big\n"

# define THREAD_EAGAIN	"Insufficient resources to create another thread.\n"
# define THREAD_EINVAL1	"Invalid settings in attr.\n"
# define THREAD_EINVAL2	"Thread is not a joinable thread or another thread \
is already waiting to join with this thread.\n"
# define THREAD_EPERM	"No permission to set the scheduling policy \
and parameters specified in attr.\n"
# define THREAD_EDEADLK	"A deadlock was detected or thread specifies \
the calling thread.\n"
# define THREAD_ESRCH	"No thread with the ID thread could be found.\n"

typedef struct s_forks
{
	bool	first_fork;
	bool	second_fork;
}	t_forks;

typedef enum e_ops
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_ops;

typedef enum e_return_value_routine
{
	QUIT,
	CONTINUE,
}	t_return_value_routine;

typedef enum e_return_value
{
	FAIL,
	SUCCESS,
}	t_return_value;

typedef enum e_thinking_helper
{
	FIRST,
	NON_FIRST,
}	t_thinking_helper;

typedef struct s_global_data	t_global_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				current_process;
	size_t			start;
	size_t			current;
	size_t			last_meal;
	int				meal_count;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_global_data	*globals;
}	t_philo;

typedef struct s_global_data
{
	pthread_mutex_t	msg_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	start_lock;
	bool			start_flag;
	pthread_mutex_t	*forks;
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				stop_simulation;
	t_philo			*philos;
	pthread_t		observer;
}	t_global_data;

//parsing
bool	parse_input(t_global_data *globals, int ac, char **av);
int		ft_atoi(const char *str, bool *overflow);
int		ft_isdigit(int c);

//init
void	init_philos(t_global_data *globals);
bool	init_forks(t_global_data *globals);
bool	start_the_dinner(t_global_data *globals);

//routine
bool	eating(t_philo *philo);
bool	sleeping(t_philo *philo);
bool	thinking(t_philo *philo);
void	*thread_routine(void *arg);
void	*observer_routine(void *arg);
bool	check_any_death(t_philo *philo);

//error and quit handling
void	cleanup(t_global_data *globals);
void	print_error(char *msg);
void	drop_the_forks(t_philo *philo, t_forks *forks);
void	destroy_current_forks(t_global_data *globals, int amount);
void	destroy_current_threads(t_global_data *globals, int amount);
void	cleanup_in_init(t_global_data *globals, int amount);

//utils
size_t	ft_strlen(const char *str);
size_t	get_current_time(void);
bool	ft_asleep(t_philo *philo, size_t sleep_in_ms, t_forks *forks);
int		msg_broadcast(t_philo *philo, char *msg, int death, t_forks *forks);

//handles
bool	thread_handle(pthread_t *thread, void *data,
			void *(*function)(void *), t_ops op);
bool	mutex_handle(pthread_mutex_t *mutex, t_ops op);

#endif
