/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:58:29 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 12:57:27 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thread_error(int return_value, t_ops op)
{
	if (return_value == 0)
		return ;
	if (return_value == EAGAIN)
		print_error("Insufficient resources to create another thread.");
	else if (return_value == EINVAL && op == CREATE)
		print_error("Invalid settings in attr.");
	else if (return_value == EINVAL && op == JOIN)
		print_error("Thread is not a joinable thread or another thread is already waiting to join with this thread.");
	else if (return_value == EPERM)
		print_error("No permission to set the scheduling policy and parameters specified in attr.");
	else if (return_value == EDEADLK)
		print_error("A deadlock was detected or thread specifies the calling thread.");
	else if (return_value == ESRCH)
		print_error("No thread with the ID thread could be found.");
	else
		print_error("Unknown thread error occurred.");
}

void	thread_handle(pthread_t *thrd, void *data, void *(*func)(void *), t_ops op)
{
	if (op == CREATE)
		thread_error(pthread_create(thrd, NULL, func, data), op);
	if (op == JOIN)
		thread_error(pthread_join(*thrd, NULL), op);
}

bool	mutex_error(int return_value, t_ops op)
{
	if (return_value == 0)
		return (SUCCESS);
	if (return_value == EAGAIN)
		print_error("Max recursive locks exceeded or resource limit reached.");
	else if (return_value == EINVAL && op == INIT)
		print_error("Invalid mutex attributes.");
	else if (return_value == EINVAL && (op == LOCK || op == UNLOCK))
		print_error("Thread priority too high for mutex.");
	else if (return_value == ENOMEM)
		print_error("Insufficient memory for mutex operation.");
	else if (return_value == EPERM)
		print_error("No permission for this mutex operation.");
	else if (return_value == EDEADLK)
		print_error("Deadlock detected or thread already owns mutex.");
	else if (return_value == ENOTRECOVERABLE)
		print_error("Mutex state not recoverable.");
	else if (return_value == EOWNERDEAD)
		print_error("Previous mutex owner terminated unexpectedly.");
	else
		print_error("Unknown mutex error occurred.");
	return (FAIL);
}

// int	failing_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
// {
// 	static int call_count = 0;
// 	call_count++;
// 	if (call_count == 3)
// 		return EAGAIN;
// 	return pthread_mutex_init(mutex, attr);
// }

bool	mutex_handle(pthread_mutex_t *mutex, t_ops op)
{
	if (op == INIT)
	{
		if (mutex_error(pthread_mutex_init(mutex, NULL), op) == FAIL)
			return (FAIL);
	}
	if (op == LOCK)
		mutex_error(pthread_mutex_lock(mutex), op);
	if (op == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), op);
	if (op == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), op);
	return (SUCCESS);
}
