/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_threads.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:41:06 by vlopatin          #+#    #+#             */
/*   Updated: 2025/02/19 10:50:49 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	process1(int id)
{
	printf("Eating, I am thread %i\n", id);
	usleep (1000000);
}

void	process2(int id)
{
	printf("Sleeping, I am thread %i\n", id);
	usleep (1500000);
}

void	process3(int id)
{
	printf("Thinking, I am thread %i\n", id);
	usleep (2400000);
}

void	*thread_routine(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	int current_process = data->starting_process;
	while (*(data->should_continue) == 1)
	{
		if (current_process == 1)
		{
			process1(data->id);
			current_process = 2;
		}
		if (current_process == 2)
		{
			process2(data->id);
			current_process = 3;
		}
		if (current_process == 3)
		{
			process3(data->id);
			current_process = 1;
		}
	}
	return NULL;
}

int	main(int ac, char **av)
{
	// if (ac != 5 && ac != 6)
		// exit_error(1, NULL);
	(void)ac;
	(void)av;

	// pthread_t threads[3];
	t_thread_data thread_data[3];
	int should_continue = 1;

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	thread_data[0].id = 1;
	thread_data[1].id = 2;
	thread_data[2].id = 3;

	thread_data[0].should_continue = &should_continue;
	thread_data[1].should_continue = &should_continue;
	thread_data[2].should_continue = &should_continue;

	thread_data[0].starting_process = 1;
	thread_data[1].starting_process = 2;
	thread_data[2].starting_process = 3;

	pthread_create(&thread1, NULL, thread_routine, &thread_data[0]);
	pthread_create(&thread2, NULL, thread_routine, &thread_data[1]);
	pthread_create(&thread3, NULL, thread_routine, &thread_data[2]);

	sleep(10);
	should_continue = 0;
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	return (0);
}
