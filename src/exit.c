/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:43:47 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 09:48:59 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	exit_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
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

void	destroy_forks(t_global_data *globals)
{
	int	i;

	i = 0;
	while (i < globals->amount)
	{
		mutex_handle(&globals->forks[i], DESTROY);
		i++;
	}
}
