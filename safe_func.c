/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:53:00 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/24 11:01:59 by ljussiau         ###   ########.fr       */
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

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
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