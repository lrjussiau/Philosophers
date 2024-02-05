/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:22:15 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/05 10:09:37 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	bool	ret;
	long	laps;
	long	t_die;

	ret = false;
	if (get_bool(&philo->mutex_philo, &philo->full))
		return (ret);
	laps = gettime(MILLISECOND) - get_long(&philo->mutex_philo,
			&philo->t_last_meal);
	t_die = philo->data->t_die / 1e3;
	if (laps > t_die)
	{
		ret = true;
	}
	return (ret);
}

void	*monitor_diner(void *value)
{
	t_data	*data;
	int		i;

	data = (t_data *)value;
	while (!all_thread_run(&data->mutex_data, &data->nb_thread_run,
			data->nb_philo))
		continue ;
	while (!simulation_finish(data))
	{
		i = -1;
		while (++i < data->nb_philo && !simulation_finish(data))
		{
			if (philo_died(data->philo + i))
			{
				set_bool(&data->mutex_data, &data->end_simulation, true);
				write_status(DIED, data->philo + i);
			}
		}
	}
	return (NULL);
}
