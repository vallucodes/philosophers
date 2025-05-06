//for testing failing mutex or thread
// call like this

if (mutex_error(failing_pthread_mutex_init(mutex, NULL), op) == FAIL)
if (thread_error(failingpthread_create(thrd, NULL, func, data), op) == FAIL)

int	failing_pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
	static int call_count = 0;
	call_count++;
	if (call_count == 3)
		return EAGAIN;
	return pthread_create(thread, attr, start_routine, arg);
}


int	failing_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	static int call_count = 0;
	call_count++;
	if (call_count == 3)
	{
		errno = EAGAIN;
		return -1;
	}
	return pthread_mutex_init(mutex, attr);
}
