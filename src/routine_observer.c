/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_observer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:11:58 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 20:20:53 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	check_meals_eaten(t_global_data *globals, int i, bool *meals_flag)
{
	if (globals->philos[i].meal_count < globals->meals && globals->meals != -1)
		*meals_flag = 0;
}

static bool	check_starvation(t_global_data *globals, int i)
{
	if (globals->philos[i].last_meal < get_current_time())
	{
		if (get_current_time() - globals->philos[i].last_meal
			>= (size_t)globals->time_to_die)
		{
			msg_broadcast(&globals->philos[i], DEATH, 1, NULL);
			pthread_mutex_unlock(&globals->meal_lock);
			return (QUIT);
		}
	}
	return (CONTINUE);
}

static bool	check_death(t_global_data *globals)
{
	int		i;
	bool	meals_flag;

	i = -1;
	meals_flag = 1;
	while (++i < globals->amount)
	{
		pthread_mutex_lock(&globals->meal_lock);
		if (check_starvation(globals, i) == QUIT)
			return (QUIT);
		check_meals_eaten(globals, i, &meals_flag);
		pthread_mutex_unlock(&globals->meal_lock);
	}
	if (meals_flag == 1 && globals->meals != -1)
	{
		msg_broadcast(&globals->philos[0], NULL, 2, NULL);
		return (QUIT);
	}
	return (CONTINUE);
}

void	*observer_routine(void *arg)
{
	t_global_data	*globals;

	globals = (t_global_data *)arg;
	while (1)
		if (check_death(globals) == QUIT)
			break ;
	return (arg);
}
