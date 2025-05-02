/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:39:19 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 09:47:20 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> //NULL
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <pthread.h> //threads
# include <unistd.h> //usleep, write
# include <limits.h> //LONG_MIN LONG_MAX
# include <errno.h> //errno
# include <stdbool.h> //bool
# include <stdint.h> //SIZE_MAX

# define ARGS1		"Incorrect amount of arguments\n"
# define ARGS2		"Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] "
# define ARGS3		"[time_to_sleep] ([number_of_times_each_philosopher_must_eat])\n"
# define MALLOC		"malloc failure"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define FORK		"has taken a fork"
# define DEATH		"died"
# define QUIT		1
# define CONTINUE	0

# define INPUT			"Error: input not valid, must be numeric"
# define AMOUNT			"Error: amount of philosophers must be between 1 and 1000"
# define TIME_TO_DIE	"Error: time to die must be greater than 0"
# define TIME_TO_EAT	"Error: time to eat must be greater than 0"
# define TIME_TO_SLEEP	"Error: time to sleep must be greater than 0"
# define MEALS			"Error: am ount of meals must be greater than 0"
# define OVERFLOW		"One of the values is too big"

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

typedef enum e_thinking_helper
{
	FIRST,
	NON_FIRST,
}	t_thinking_helper;

typedef struct s_global_data t_global_data;

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
	pthread_mutex_t meal_lock;
	pthread_mutex_t start_lock;
	bool			start_flag;
	pthread_mutex_t	*forks;
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				stop_simulation;
	t_philo			*philos;
}	t_global_data;

/*
	Return value of 0 in fucntions means fail/death, 1 stands for everything is fine.
*/

//parsing

void	parse_input(t_global_data *globals, int ac, char **av);
void	validate_input(char **av);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

//init
void	init_philos(t_global_data *globals);
// void	assign_forks(t_global_data *globals, t_philo *philo, int i);
void	init_forks(t_global_data *globals);
void	start_the_dinner(t_global_data *globals);

//routine
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
void	*thread_routine(void *arg);
void	*observer_routine(void *arg);

//exit
void	exit_error(char *msg);
void	destroy_forks(t_global_data *globals);
void	drop_the_forks(t_philo *philo, t_forks *forks);

//utils
size_t	get_current_time();
bool	ft_asleep(t_philo *philo, size_t sleep_in_ms, t_forks *forks);
int		msg_broadcast(t_philo *philo, char *msg, int death, t_forks *forks);

//handles
void	thread_error(int return_value, t_ops op);
void	thread_handle(pthread_t *thread, void *data, void *(*function)(void *), t_ops op);
void	mutex_error(int return_value, t_ops op);
void	mutex_handle(pthread_mutex_t *mutex, t_ops op);

bool	check_any_death(t_philo *philo);

#endif
