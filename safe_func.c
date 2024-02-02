/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:53:00 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 07:28:21 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(unsigned int bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error("malloc failed");
	else
		return (ret);
}

static void	handle_mutex_error(int status, t_mutexcode mutex_code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (mutex_code == LOCK || mutex_code == UNLOCK))
		error("The value specified by mutex is invalid");
	else if (status == EINVAL && mutex_code == INIT)
		error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error("A deadlock would occur if the thread waiting for mutex.");
	else if (status == EPERM)
		error("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error("The process cannot allocate enough memory to create mutex.");
	else if (status == EBUSY)
		error("Mutex is locked");
}

static void	handle_thread_error(int status, t_threadcode thread_code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (thread_code == JOIN || thread_code == DETACH))
		error("The value does not refer to a joinable thread.");
	else if (status == EINVAL && thread_code == CREATE)
		error("The value specified by attr is invalid.");
	else if (status == ESRCH)
		error("No thread could be found by the given thread ID, thread.");
	else if (status == EDEADLK)
		error("A deadlock was detected specifies the calling thread.");
	else if (status == EPERM)
		error("The caller does not have appropriate permission.");
	else if (status == EAGAIN)
		error("No resources to create another thread");
}

void	safe_mutex(pthread_mutex_t *mutex, t_mutexcode mutex_code)
{
	if (mutex_code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), mutex_code);
	else if (mutex_code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), mutex_code);
	else if (mutex_code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), mutex_code);
	else if (mutex_code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), mutex_code);
	else
		error("Wrong Mutex code");
}

void	safe_thread(pthread_t *thread, t_threadcode thread_code,
			void *data, void *(*foo)(void *))
{
	if (thread_code == JOIN)
		handle_thread_error(pthread_join(thread, NULL), thread_code);
	else if (thread_code == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data),
			thread_code);
	else if (thread_code == DETACH)
		handle_thread_error(pthread_detach(thread), thread_code);
	else
		error("Wrong Thread code");
}
