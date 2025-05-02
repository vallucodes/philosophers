/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:43:47 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 20:04:18 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	cleanup(t_global_data *globals)
{
	free(globals->philos);
	free(globals->forks);
}

void	drop_the_forks(t_philo *philo, t_forks *forks)
{
	if (forks)
	{
		if (forks->first_fork == true)
			mutex_handle(philo->first_fork, UNLOCK);
		if (forks->second_fork == true)
			mutex_handle(philo->second_fork, UNLOCK);
	}
}

void	destroy_current_forks(t_global_data *globals, int amount)
{
	while (--amount >= 0)
		mutex_handle(&globals->forks[amount], DESTROY);
}

void	destroy_current_threads(t_global_data *globals, int amount)
{
	while (--amount >= 0)
		thread_handle(&globals->philos[amount].thread, NULL, NULL, JOIN);
}

void	cleanup_in_init(t_global_data *globals, int amount)
{
	destroy_current_threads(globals, amount);
	destroy_current_forks(globals, globals->amount);
	mutex_handle(&globals->msg_lock, DESTROY);
	mutex_handle(&globals->death_lock, DESTROY);
	mutex_handle(&globals->meal_lock, DESTROY);
	mutex_handle(&globals->start_lock, DESTROY);
	cleanup(globals);
}
