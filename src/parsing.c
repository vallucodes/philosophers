/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:09:16 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 10:23:39 by vlopatin         ###   ########.fr       */
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
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]) && !(av[i][0] == '-'))
				return(print_error(INPUT), FAIL);
		}
	}
	return (SUCCESS);
}

bool	parse_input(t_global_data *globals, int ac, char **av)
{
	bool	overflow;

	overflow = 0;
	if (validate_input(av) == FAIL)
		return (FAIL);
	globals->amount = ft_atoi(av[1], &overflow);
	if (globals->amount <= 0 || globals->amount > 1000)
		return(print_error(AMOUNT), FAIL);
	globals->time_to_die = ft_atoi(av[2], &overflow);
	if (globals->time_to_die <= 0)
		return(print_error(TIME_TO_DIE), FAIL);
	globals->time_to_eat = ft_atoi(av[3], &overflow);
	if (globals->time_to_eat <= 0)
		return(print_error(TIME_TO_EAT), FAIL);
	globals->time_to_sleep = ft_atoi(av[4], &overflow);
	if (globals->time_to_sleep <= 0)
		return(print_error(TIME_TO_SLEEP), FAIL);
	if (ac == 6)
	{
		globals->meals = ft_atoi(av[5], &overflow);
		if (globals->meals <= 0)
			return(print_error(MEALS), FAIL);
	}
	else
		globals->meals = -1;
	globals->stop_simulation = 0;
	if (overflow == 1)
		return (print_error(OVERFLOW), FAIL);
	return (SUCCESS);
}
