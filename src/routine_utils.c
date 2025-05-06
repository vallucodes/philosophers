/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:32:58 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/06 16:57:32 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	there_is_death_or_enough_meals(int death)
{
	return (death == 1 || death == 2);
}

int	msg_broadcast(t_philo *philo, char *msg, int death, t_forks *forks)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->globals->msg_lock);
	if (check_any_death(philo) == QUIT)
	{
		drop_the_forks(philo, forks);
		return (pthread_mutex_unlock(&philo->globals->msg_lock), 0);
	}
	if (death != 2)
	{
		timestamp = (get_current_time() - philo->start);
		printf("%li %i %s\n", timestamp, philo->id, msg);
	}
	if (there_is_death_or_enough_meals(death))
	{
		pthread_mutex_lock(&philo->globals->death_lock);
		philo->globals->stop_simulation = 1;
		pthread_mutex_unlock(&philo->globals->death_lock);
		drop_the_forks(philo, forks);
		return (pthread_mutex_unlock(&philo->globals->msg_lock), 0);
	}
	pthread_mutex_unlock(&philo->globals->msg_lock);
	return (CONTINUE);
}

size_t	get_current_time(void)
{
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) == -1)
		write(2, "Error gettimeofday()\n", 21);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

bool	check_any_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->globals->death_lock);
	if (philo->globals->stop_simulation == 1)
	{
		pthread_mutex_unlock(&philo->globals->death_lock);
		return (QUIT);
	}
	pthread_mutex_unlock(&philo->globals->death_lock);
	return (CONTINUE);
}

bool	ft_asleep(t_philo *philo, size_t sleep_in_ms, t_forks *forks)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < sleep_in_ms)
	{
		if (check_any_death(philo) == QUIT)
		{
			drop_the_forks(philo, forks);
			return (QUIT);
		}
		usleep(300);
	}
	return (CONTINUE);
}
