/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:26:52 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/05 08:36:10 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->mutex_data, &data->all_thread_ready))
		continue ;
}

bool	all_thread_run(pthread_mutex_t *mutex, long *thread, long philo_nb)
{
	bool	ret;

	ret = false;
	safe_mutex(mutex, LOCK);
	if (*thread == philo_nb)
		ret = true;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}
