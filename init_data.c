/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:53:00 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 07:27:33 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_data *data)
{
    
}

void	init(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = false;
	data->philo = safe_malloc(sizeof(t_philo) * data->nb_philo);
	data->fork = safe_malloc(sizeof(t_fork) * data->nb_philo);
	while (i < data->nb_philo)
	{
		safe_mutex(&data->fork[i].fork, INIT);
		data->fork[i].id = i;
	}
	philo_init(data);
}
