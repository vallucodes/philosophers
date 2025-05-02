/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:47:04 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 09:42:26 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	eating(t_philo *philo)
{
	t_forks	forks;

	forks.first_fork = false;
	forks.second_fork = false;
	mutex_handle(philo->first_fork, LOCK);
	forks.first_fork = true;
	if (!msg_broadcast(philo, FORK, 0, &forks))
		return (QUIT);
	if (philo->globals->amount == 1)
	{
		ft_asleep(philo, philo->globals->time_to_die + 200, &forks);
		return (QUIT);
	}
	mutex_handle(philo->second_fork, LOCK);
	forks.second_fork = true;
	if (!msg_broadcast(philo, FORK, 0, &forks))
		return (QUIT);
	if (!msg_broadcast(philo, EATING, 0, &forks))
		return (QUIT);
	mutex_handle(&philo->globals->meal_lock, LOCK);
	philo->meal_count += 1;
	philo->last_meal = get_current_time();
	mutex_handle(&philo->globals->meal_lock, UNLOCK);
	if (ft_asleep(philo, philo->globals->time_to_eat, &forks) == QUIT)
		return (QUIT);
	mutex_handle(philo->first_fork, UNLOCK);
	forks.first_fork = false;
	mutex_handle(philo->second_fork, UNLOCK);
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
	t_philo *philo;

	philo = (t_philo *)arg;
	waiting_to_start(philo);
	philo->start = get_current_time();
	philo->last_meal = philo->start;
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
