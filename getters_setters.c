/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:13:26 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 10:46:09 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	safe_mutex(mutex, LOCK);
	ret = *value;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

bool	simulation_finish(t_data *data)
{
	return (get_bool(&data->mutex_data, &data->end_simulation));
}
