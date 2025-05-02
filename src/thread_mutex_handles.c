/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex_handles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:58:29 by vlopatin          #+#    #+#             */
/*   Updated: 2025/05/02 17:09:00 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	thread_error(int return_value, t_ops op)
{
	if (return_value == 0)
		return (SUCCESS);
	if (return_value == EAGAIN)
		print_error(THREAD_EAGAIN);
	else if (return_value == EINVAL && op == CREATE)
		print_error(THREAD_EINVAL1);
	else if (return_value == EINVAL && op == JOIN)
		print_error(THREAD_EINVAL2);
	else if (return_value == EPERM)
		print_error(THREAD_EPERM);
	else if (return_value == EDEADLK)
		print_error(THREAD_EDEADLK);
	else if (return_value == ESRCH)
		print_error(THREAD_ESRCH);
	else
		print_error("Unknown thread error occurred.\n");
	return (FAIL);
}

bool	thread_handle(pthread_t *thrd, void *data,
						void *(*func)(void *), t_ops op)
{
	if (op == CREATE)
	{
		if (thread_error(pthread_create(thrd, NULL, func, data), op) == FAIL)
			return (FAIL);
	}
	if (op == JOIN)
		thread_error(pthread_join(*thrd, NULL), op);
	return (SUCCESS);
}

static bool	mutex_error(int return_value, t_ops op)
{
	if (return_value == 0)
		return (SUCCESS);
	if (return_value == EAGAIN)
		print_error("Max recursive locks exceeded or resource limit reached.\n");
	else if (return_value == EINVAL && op == INIT)
		print_error("Invalid mutex attributes.\n");
	else if (return_value == EINVAL && (op == LOCK || op == UNLOCK))
		print_error("Thread priority too high for mutex.\n");
	else if (return_value == ENOMEM)
		print_error("Insufficient memory for mutex operation.\n");
	else if (return_value == EPERM)
		print_error("No permission for this mutex operation.\n");
	else if (return_value == EDEADLK)
		print_error("Deadlock detected or thread already owns mutex.\n");
	else if (return_value == ENOTRECOVERABLE)
		print_error("Mutex state not recoverable.\n");
	else if (return_value == EOWNERDEAD)
		print_error("Previous mutex owner terminated unexpectedly.\n");
	else
		print_error("Unknown mutex error occurred.\n");
	return (FAIL);
}

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
