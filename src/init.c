/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:08:35 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 16:07:42 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	collect_threads_stop_simulation(t_global_data *globals)
{
	mutex_handle(&globals->start_lock, LOCK);
	globals->start_flag = 1;
	mutex_handle(&globals->start_lock, UNLOCK);
	pthread_mutex_lock(&globals->death_lock);
	globals->stop_simulation = 1;
	pthread_mutex_unlock(&globals->death_lock);
}

bool	start_the_dinner(t_global_data *globals)
{
	int			i;
	t_philo		*philo;

	philo = globals->philos;
	i = 0;
	while (i < globals->amount)
	{
		if (thread_handle(&philo[i].thread, &philo[i],
				thread_routine, CREATE) == FAIL)
		{
			collect_threads_stop_simulation(globals);
			return (cleanup_in_init(globals, i), FAIL);
		}
		i++;
	}
	if (thread_handle(&globals->observer, globals,
			observer_routine, CREATE) == FAIL)
	{
		collect_threads_stop_simulation(globals);
		return (cleanup_in_init(globals, globals->amount), FAIL);
	}
	mutex_handle(&philo->globals->start_lock, LOCK);
	globals->start_flag = 1;
	mutex_handle(&philo->globals->start_lock, UNLOCK);
	return (SUCCESS);
}

static void	assign_forks(t_global_data *globals, t_philo *philo, int i)
{
	if (globals->amount == 1)
	{
		philo->first_fork = &globals->forks[i];
		philo->second_fork = NULL;
		return ;
	}
	if (philo->id % 2)
	{
		philo->first_fork = &globals->forks[(i + 1) % globals->amount];
		philo->second_fork = &globals->forks[i];
	}
	else
	{
		philo->first_fork = &globals->forks[i];
		philo->second_fork = &globals->forks[(i + 1) % globals->amount];
	}
}

void	init_philos(t_global_data *globals)
{
	int		i;
	t_philo	*philo;

	philo = globals->philos;
	i = 0;
	while (i < globals->amount)
	{
		philo[i].id = i + 1;
		assign_forks(globals, &philo[i], i);
		philo[i].current_process = 0;
		philo[i].meal_count = 0;
		philo[i].start = SIZE_MAX;
		philo[i].last_meal = SIZE_MAX;
		philo[i].globals = globals;
		i++;
	}
}

bool	init_forks(t_global_data *globals)
{
	int	i;

	i = 0;
	while (i < globals->amount)
	{
		if (mutex_handle(&globals->forks[i], INIT) == FAIL)
			return (destroy_current_forks(globals, i), FAIL);
		i++;
	}
	return (SUCCESS);
}
