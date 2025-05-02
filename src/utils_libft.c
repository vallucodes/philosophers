/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:57:04 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 16:56:25 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str, bool *overflow)
{
	int		i;
	long	result;

	result = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		if (result > 2147483647)
		{
			*overflow = 1;
			return (1);
		}
		i++;
	}
	return ((int)result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
