/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:41:06 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 16:07:55 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	cleanup_and_free(t_global_data *globals)
{
	thread_handle(&globals->observer, NULL, NULL, JOIN);
	cleanup_in_init(globals, globals->amount);
}

static bool	init_mutexes(t_global_data *globals)
{
	if (init_forks(globals) == FAIL)
		return (FAIL);
	if (mutex_handle(&globals->msg_lock, INIT) == FAIL)
		return (destroy_current_forks(globals, globals->amount), FAIL);
	if (mutex_handle(&globals->death_lock, INIT) == FAIL)
	{
		mutex_handle(&globals->msg_lock, DESTROY);
		return (destroy_current_forks(globals, globals->amount), FAIL);
	}
	if (mutex_handle(&globals->meal_lock, INIT) == FAIL)
	{
		mutex_handle(&globals->msg_lock, DESTROY);
		mutex_handle(&globals->death_lock, DESTROY);
		return (destroy_current_forks(globals, globals->amount), FAIL);
	}
	if (mutex_handle(&globals->start_lock, INIT) == FAIL)
	{
		mutex_handle(&globals->msg_lock, DESTROY);
		mutex_handle(&globals->death_lock, DESTROY);
		mutex_handle(&globals->meal_lock, DESTROY);
		return (destroy_current_forks(globals, globals->amount), FAIL);
	}
	return (SUCCESS);
}

static bool	init_program(t_global_data *globals)
{
	globals->philos = NULL;
	globals->forks = NULL;
	globals->philos = malloc(sizeof(t_philo) * globals->amount);
	if (!globals->philos)
		return (print_error(MALLOC), FAIL);
	globals->forks = malloc(sizeof(pthread_mutex_t) * globals->amount);
	if (!globals->forks)
	{
		cleanup(globals);
		return (print_error(MALLOC), FAIL);
	}
	if (init_mutexes(globals) == FAIL)
		return (cleanup(globals), FAIL);
	globals->start_flag = 0;
	return (SUCCESS);
}

bool	go_to_the_table(t_global_data *globals)
{
	if (init_program(globals) == FAIL)
		return (FAIL);
	init_philos(globals);
	if (start_the_dinner(globals) == FAIL)
		return (FAIL);
	cleanup_and_free(globals);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_global_data	globals;

	if (ac != 5 && ac != 6)
		return (print_error(ARGS1 ARGS2 ARGS3), 1);
	if (parse_input(&globals, ac, av) == FAIL)
		return (1);
	if (go_to_the_table(&globals) == FAIL)
		return (1);
	return (0);
}
