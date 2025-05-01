/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:41:06 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/01 14:58:05 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <signal.h>

void	cleanup_and_free(t_global_data *globals)
{
	int i;

	i = 0;
	while (i < globals->amount)
		thread_handle(&globals->philos[i++].thread, NULL, NULL, JOIN);
	destroy_forks(globals);
	mutex_handle(&globals->msg_lock, DESTROY);
	free(globals->philos);
	free(globals->forks);
}

void	init_program(t_global_data *globals)
{
	globals->philos = malloc(sizeof(t_philo) * globals->amount);
	if (!globals->philos)
		exit_error(MALLOC);
	globals->forks = malloc(sizeof(pthread_mutex_t) * globals->amount);
	if (!globals->forks)
	{
		free(globals->philos);
		exit_error(MALLOC);
	}
	init_forks(globals);
	mutex_handle(&globals->msg_lock, INIT);
	mutex_handle(&globals->death_lock, INIT);
	mutex_handle(&globals->meal_lock, INIT);
}

int	init_threads(t_global_data *globals)
{
	init_program(globals);
	init_philos(globals);
	start_the_dinner(globals);
	cleanup_and_free(globals);
	return (0);
}

//to-do

// make better logic for checking if meals are eaten
// make mathematical models of how to calculate tipping point of death for even and odd


int	main(int ac, char **av)
{
	t_global_data	globals;

	if (ac != 5 && ac != 6)
		exit_error(ARGS1 ARGS2 ARGS3);
	parse_input(&globals, ac, av);
	if (globals.meals == 0)
		return (0);
	init_threads(&globals);
	return (0);
}


// cases
// no death
// ./philo 5 1000 300 100
// ./philo 3 200 65 65 5
// ./philo 5 600 150 150
// death
