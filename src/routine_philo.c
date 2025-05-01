/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:47:04 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/01 17:15:25 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	eating(t_philo *philo)
{
	t_forks	forks;

	forks.first_fork = false;
	forks.second_fork = false;
	// mutex_handle(philo->first_fork, LOCK);
	mutex_handle(philo->first_fork, LOCK);
	// pthread_mutex_lock(philo->first_fork);
	forks.first_fork = true;
	if (!msg_broadcast(philo, FORK, 0, &forks))
		return (QUIT);
	if (philo->globals->amount == 1)
	{
		ft_asleep(philo, philo->globals->time_to_die + 200, &forks);
		return (QUIT);
	}
	mutex_handle(philo->second_fork, LOCK);
	// pthread_mutex_lock(philo->second_fork);
	forks.second_fork = true;
	if (!msg_broadcast(philo, FORK, 0, &forks))
		return (QUIT);
	if (!msg_broadcast(philo, EATING, 0, &forks))
		return (QUIT);
	mutex_handle(&philo->globals->meal_lock, LOCK);
	// pthread_mutex_lock(&philo->globals->meal_lock);
	philo->meal_count += 1;
	philo->last_meal = get_current_time();
	mutex_handle(&philo->globals->meal_lock, UNLOCK);
	// pthread_mutex_unlock(&philo->globals->meal_lock);
	if (ft_asleep(philo, philo->globals->time_to_eat, &forks) == QUIT)
		return (QUIT);
	mutex_handle(philo->first_fork, UNLOCK);
	// pthread_mutex_unlock(philo->first_fork);
	// printf("Im %i, dropped first fork\n", philo->id);
	forks.first_fork = false;
	mutex_handle(philo->second_fork, UNLOCK);
	// pthread_mutex_unlock(philo->second_fork);
	// printf("Im %i, dropped second fork\n", philo->id);
	forks.second_fork = false;
	return (CONTINUE);
}

int	sleeping(t_philo *philo)
{
	if (!msg_broadcast(philo, SLEEPING, 0, NULL))
		return (QUIT);
	if (ft_asleep(philo, philo->globals->time_to_sleep, NULL) == QUIT)
		return (QUIT);
	return (CONTINUE);
}

int	thinking(t_philo *philo)
{
	int	t_to_think;

	if (msg_broadcast(philo, THINKING, 0, NULL) == 0)
		return (QUIT);
	if (philo->globals->amount % 2 == 0)
		return (CONTINUE);
	t_to_think = philo->globals->time_to_eat - philo->globals->time_to_sleep + 10;
	if (t_to_think < 0)
		t_to_think = 0;
	if (ft_asleep(philo, t_to_think, NULL) == QUIT)
		return (QUIT);
	return (CONTINUE);
}

void	*thread_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
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
	while (check_any_death(philo) == CONTINUE)
	{
		if (philo->current_process == 0)
		{
			if (eating(philo) == QUIT)
				return (NULL);
			philo->current_process = 1;
		}
		if (philo->current_process == 1)
		{
			if (sleeping(philo) == QUIT)
				return (NULL);
			philo->current_process = 2;
		}
		if (philo->current_process == 2)
		{
			if (thinking(philo) == QUIT)
				return (NULL);
			philo->current_process = 0;
		}
	}
	return (NULL);
}


// int	thinking(t_philo *philo, bool thinking)
// {
// 	int	t_to_think;

// 	if (msg_broadcast(philo, THINKING, 0, NULL) == 0)
// 		return (QUIT);
// 	if (philo->globals->amount % 2 == 0)
// 		return (CONTINUE);
// 	if (thinking == NON_FIRST)
// 	{
// 		t_to_think = philo->globals->time_to_eat - philo->globals->time_to_sleep + 20;
// 		if (t_to_think < 0)
// 			t_to_think = 0;
// 		if (ft_asleep(philo, t_to_think, NULL) == QUIT)
// 			return (QUIT);
// 	}
// 	else
// 	{
// 		t_to_think = 30;
// 		if (ft_asleep(philo, t_to_think, NULL) == QUIT)
// 			return (QUIT);
// 	}
// 	return (CONTINUE);
// }
