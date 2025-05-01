/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:09:16 by vlopatin          #+#    #+#             */
/*   Updated: 2025/03/10 21:15:18 by vlopatin         ###   ########.fr       */
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
			if (!ft_isdigit(av[i][j]))
				exit_error(INPUT);
		}
	}
}

void	parse_input(t_global_data *globals, int ac, char **av)
{
	validate_input(av);
	globals->amount = ft_atoi(av[1]);
	globals->time_to_die = ft_atoi(av[2]);
	globals->time_to_eat = ft_atoi(av[3]);
	globals->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		globals->meals = ft_atoi(av[5]);
	else
		globals->meals = -1;
	globals->stop_simulation = 0;
}
