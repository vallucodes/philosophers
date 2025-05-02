/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:14:20 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 20:46:24 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	pick_the_forks(t_philo *philo, t_forks *forks)
{
	mutex_handle(philo->first_fork, LOCK);
	forks->first_fork = true;
	if (!msg_broadcast(philo, FORK, 0, forks))
		return (QUIT);
	if (philo->globals->amount == 1)
	{
		ft_asleep(philo, philo->globals->time_to_die + 200, forks);
		return (QUIT);
	}
	mutex_handle(philo->second_fork, LOCK);
	mutex_handle(&philo->globals->meal_lock, LOCK);
	philo->meal_count += 1;
	philo->last_meal = get_current_time();
	mutex_handle(&philo->globals->meal_lock, UNLOCK);
	forks->second_fork = true;
	if (!msg_broadcast(philo, FORK, 0, forks))
		return (QUIT);
	return (CONTINUE);
}

static bool	eat_spaghetti(t_philo *philo, t_forks *forks)
{
	if (!msg_broadcast(philo, EATING, 0, forks))
		return (QUIT);
	if (ft_asleep(philo, philo->globals->time_to_eat, forks) == QUIT)
		return (QUIT);
	mutex_handle(philo->first_fork, UNLOCK);
	forks->first_fork = false;
	mutex_handle(philo->second_fork, UNLOCK);
	forks->second_fork = false;
	return (CONTINUE);
}

bool	eating(t_philo *philo)
{
	t_forks	forks;

	forks.first_fork = false;
	forks.second_fork = false;
	if (pick_the_forks(philo, &forks) == QUIT)
		return (QUIT);
	if (eat_spaghetti(philo, &forks) == QUIT)
		return (QUIT);
	return (CONTINUE);
}

bool	sleeping(t_philo *philo)
{
	if (!msg_broadcast(philo, SLEEPING, 0, NULL))
		return (QUIT);
	if (ft_asleep(philo, philo->globals->time_to_sleep, NULL) == QUIT)
		return (QUIT);
	return (CONTINUE);
}

bool	thinking(t_philo *philo)
{
	int	t_to_think;
	int	t_to_eat;
	int	t_to_sleep;

	t_to_eat = philo->globals->time_to_eat;
	t_to_sleep = philo->globals->time_to_sleep;
	if (msg_broadcast(philo, THINKING, 0, NULL) == 0)
		return (QUIT);
	if (philo->globals->amount % 2 == 0)
		return (CONTINUE);
	t_to_think = t_to_eat - t_to_sleep + 10;
	if (t_to_think < 0)
		t_to_think = 0;
	if (ft_asleep(philo, t_to_think, NULL) == QUIT)
		return (QUIT);
	return (CONTINUE);
}
