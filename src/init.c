/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:08:35 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 09:49:34 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	start_the_dinner(t_global_data *globals)
{
	int			i;
	t_philo		*philo;
	pthread_t	observer;

	philo = globals->philos;
	i = 0;
	while (i < globals->amount)
	{
		thread_handle(&philo[i].thread, &philo[i], thread_routine, CREATE);
		i++;
	}
	thread_handle(&observer, globals, observer_routine, CREATE);
	mutex_handle(&philo->globals->start_lock, LOCK);
	globals->start_flag = 1;
	mutex_handle(&philo->globals->start_lock, UNLOCK);
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
	int	i;
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

void	init_forks(t_global_data *globals)
{
	int	i;

	i = 0;
	while (i < globals->amount)
	{
		mutex_handle(&globals->forks[i], INIT);
		i++;
	}
}

