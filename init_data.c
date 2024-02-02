/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:53:00 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 10:27:36 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nb;

	philo_nb = philo->data->nb_philo;
	philo->right_fork = &forks[(pos + 1) % philo_nb];
	philo->left_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[pos];
		philo->left_fork = &forks[(pos + 1) % philo_nb];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->nb_meal = 0;
		philo->data = data;
		safe_mutex(&philo->mutex_philo, INIT);
		assign_fork(philo, data->fork, i);
		i++;
	}
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
		safe_mutex(&data->mutex_data, INIT);
		safe_mutex(&data->mutex_write, INIT);
		data->fork[i].id = i;
		i++;
	}
	philo_init(data);
}
