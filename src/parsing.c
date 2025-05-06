/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:09:16 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/05 15:20:48 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	validate_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		if (av[i][0] == '\0')
			return (print_error(INPUT), FAIL);
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) || (j == 0 && (av[i][j] == '-')))
				continue ;
			else
				return (print_error(INPUT), FAIL);
		}
	}
	return (SUCCESS);
}

static bool	set_globals(t_global_data *globals,
						int ac, char **av, bool *overflow)
{
	globals->amount = ft_atoi(av[1], overflow);
	if (globals->amount <= 0 || globals->amount > 1000)
		return (print_error(AMOUNT), FAIL);
	globals->time_to_die = ft_atoi(av[2], overflow);
	if (globals->time_to_die <= 0)
		return (print_error(TIME_TO_DIE), FAIL);
	globals->time_to_eat = ft_atoi(av[3], overflow);
	if (globals->time_to_eat <= 0)
		return (print_error(TIME_TO_EAT), FAIL);
	globals->time_to_sleep = ft_atoi(av[4], overflow);
	if (globals->time_to_sleep <= 0)
		return (print_error(TIME_TO_SLEEP), FAIL);
	if (ac == 6)
	{
		globals->meals = ft_atoi(av[5], overflow);
		if (globals->meals <= 0)
			return (print_error(MEALS), FAIL);
	}
	else
		globals->meals = -1;
	globals->stop_simulation = 0;
	return (SUCCESS);
}

bool	parse_input(t_global_data *globals, int ac, char **av)
{
	bool	overflow;

	overflow = 0;
	if (validate_input(av) == FAIL)
		return (FAIL);
	if (set_globals(globals, ac, av, &overflow) == FAIL)
		return (FAIL);
	if (overflow == 1)
		return (print_error(OVERFLOW), FAIL);
	return (SUCCESS);
}
