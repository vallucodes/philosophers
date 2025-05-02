/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:47:04 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 16:17:12 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	starting_routine(t_philo *philo)
{
	if (philo->globals->amount % 2 == 1 && philo->globals->amount != 1)
	{
		if (philo->id % 2)
			thinking(philo);
	}
	if (philo->globals->amount % 2 == 0)
	{
		if (philo->id % 2)
		{
			thinking(philo);
			ft_asleep(philo, 60, NULL);
		}
	}
}

void	waiting_to_start(t_philo *philo)
{
	bool	start;

	start = 0;
	while (1)
	{
		mutex_handle(&philo->globals->start_lock, LOCK);
		start = philo->globals->start_flag;
		mutex_handle(&philo->globals->start_lock, UNLOCK);
		if (start == 1)
			return ;
	}
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	waiting_to_start(philo);
	philo->start = get_current_time();
	pthread_mutex_lock(&philo->globals->meal_lock);
	philo->last_meal = philo->start;
	pthread_mutex_unlock(&philo->globals->meal_lock);
	starting_routine(philo);
	while (check_any_death(philo) == CONTINUE)
	{
		if (eating(philo) == QUIT)
			return (NULL);
		if (sleeping(philo) == QUIT)
			return (NULL);
		if (thinking(philo) == QUIT)
			return (NULL);
	}
	return (NULL);
}
