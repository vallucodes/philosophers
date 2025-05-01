/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:58:29 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/01 14:33:40 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thread_error(int return_value, t_ops op)
{
	if (return_value == 0)
		return ;
	if (return_value == EAGAIN)
		exit_error("Insufficient resources to create another thread.");
	else if (return_value == EINVAL && op == CREATE)
		exit_error("Invalid settings in attr.");
	else if (return_value == EINVAL && op == JOIN)
		exit_error("Thread is not a joinable thread or another thread is already waiting to join with this thread.");
	else if (return_value == EPERM)
		exit_error("No permission to set the scheduling policy and parameters specified in attr.");
	else if (return_value == EDEADLK)
		exit_error("A deadlock was detected or thread specifies the calling thread.");
	else if (return_value == ESRCH)
		exit_error("No thread with the ID thread could be found.");
	else
		exit_error("Unknown thread error occurred.");
}

void	thread_handle(pthread_t *thrd, void *data, void *(*func)(void *), t_ops op)
{
	if (op == CREATE)
		thread_error(pthread_create(thrd, NULL, func, data), op);
	if (op == JOIN)
		thread_error(pthread_join(*thrd, NULL), op);
}

void	mutex_error(int return_value, t_ops op)
{
	if (return_value == 0)
		return ;
	if (return_value == EAGAIN)
		exit_error("Max recursive locks exceeded or resource limit reached.");
	else if (return_value == EINVAL && op == INIT)
		exit_error("Invalid mutex attributes.");
	else if (return_value == EINVAL && (op == LOCK || op == UNLOCK))
		exit_error("Thread priority too high for mutex.");
	else if (return_value == ENOMEM)
		exit_error("Insufficient memory for mutex operation.");
	else if (return_value == EPERM)
		exit_error("No permission for this mutex operation.");
	else if (return_value == EDEADLK)
		exit_error("Deadlock detected or thread already owns mutex.");
	else if (return_value == ENOTRECOVERABLE)
		exit_error("Mutex state not recoverable.");
	else if (return_value == EOWNERDEAD)
		exit_error("Previous mutex owner terminated unexpectedly.");
	else
		exit_error("Unknown mutex error occurred.");
}


void	mutex_handle(pthread_mutex_t *mutex, t_ops op)
{
	if (op == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL), op);
	if (op == LOCK)
		mutex_error(pthread_mutex_lock(mutex), op);
	if (op == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), op);
	if (op == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), op);
}
