/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:57:25 by vlopatin          #+#    #+#             */
/*   Updated: 2025/02/18 13:57:53 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main()
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);

	int u1 = start.tv_usec;
	int u2 = end.tv_usec;
	int s1 = start.tv_sec;
	int s2 = end.tv_sec;
	int diff_u = end.tv_usec - start.tv_usec;
	int diff_s = end.tv_sec - start.tv_sec;

	if (diff_u < 0)
	{
		diff_u += 1000000;
		diff_s--;
	}

	int diff = diff_s * 1000000 + diff_u;

	printf("sec start %i, end %i\nusec start %i, end %i\ndiff %i\n", s1, s2, u1, u2, diff);
}
