/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:33:50 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 11:07:41 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	laps;

	if (get_bool(&philo->data->mutex_data, &philo->full))
		return ;
	laps = gettime(MILLISECOND) - philo->data->time_start;
	safe_mutex(&philo->data->mutex_write, LOCK);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !simulation_finish(philo->data))
		printf("%6ld %d has taken a fork\n", laps, philo->id);
	if (status == EAT && !simulation_finish(philo->data))
		printf("%6ld %d is eating\n", laps, philo->id);
	if (status == SLEEP && !simulation_finish(philo->data))
		printf("%6ld %d is sleeping\n", laps, philo->id);
	if (status == THINK && !simulation_finish(philo->data))
		printf("%6ld %d is thinking\n", laps, philo->id);
	if (status == DIED && !simulation_finish(philo->data))
		printf("%6ld %d died !\n", laps, philo->id);
	safe_mutex(&philo->data->mutex_write, UNLOCK);
}
