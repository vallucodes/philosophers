/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:09:16 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 09:47:08 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	validate_input(char **av)
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
				exit_error(INPUT);
		}
	}
}

void	parse_input(t_global_data *globals, int ac, char **av)
{
	validate_input(av);
	globals->amount = ft_atoi(av[1]);
	if (globals->amount <= 0 || globals->amount > 1000)
		exit_error(AMOUNT);
	globals->time_to_die = ft_atoi(av[2]);
	if (globals->time_to_die <= 0)
		exit_error(TIME_TO_DIE);
	globals->time_to_eat = ft_atoi(av[3]);
	if (globals->time_to_eat <= 0)
		exit_error(TIME_TO_EAT);
	globals->time_to_sleep = ft_atoi(av[4]);
	if (globals->time_to_sleep <= 0)
		exit_error(TIME_TO_SLEEP);
	if (ac == 6)
	{
		globals->meals = ft_atoi(av[5]);
		if (globals->meals <= 0)
			exit_error(MEALS);
	}
	else
		globals->meals = -1;
	globals->stop_simulation = 0;
}
