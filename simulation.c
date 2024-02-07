/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:53:47 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/05 10:18:10 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void	*value)
{
	t_philo	*philo;

	philo = (t_philo *)value;
	wait_all_threads(philo->data);
	set_long(&philo->mutex_philo, &philo->t_last_meal, gettime(MILLISECOND));
	increase_long(&philo->data->mutex_data, &philo->data->nb_thread_run);
	while (!simulation_finish(philo->data))
		usleep(500);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex(&philo->right_fork->fork, LOCK);
	write_status(TAKE_RIGHT_FORK, philo);
	safe_mutex(&philo->left_fork->fork, LOCK);
	write_status(TAKE_LEFT_FORK, philo);
	set_long(&philo->mutex_philo, &philo->t_last_meal, gettime(MILLISECOND));
	philo->nb_meal++;
	write_status(EAT, philo);
	precise_usleep(philo->data->t_eat, philo->data);
	if (philo->data->nb_max_meal > 0
		&& philo->nb_meal == philo->data->nb_max_meal)
		set_bool(&philo->mutex_philo, &philo->full, true);
	safe_mutex(&philo->right_fork->fork, UNLOCK);
	safe_mutex(&philo->left_fork->fork, UNLOCK);
}

void	think(t_philo *philo, bool odd_philo)
{
	if (odd_philo)
		write_status(THINK, philo);

	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!odd_philo)
		write_status(THINK, philo);
	if (philo->data->nb_philo % 2 == 0)
		return ;
	t_eat = philo->data->t_eat;
	t_sleep = philo->data->t_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->data);
}

static void	*dinner_simulation(void *dt)
{
	t_philo	*philo;

	philo = (t_philo *)dt;
	wait_all_threads(philo->data);
	increase_long(&philo->data->mutex_data, &philo->data->nb_thread_run);
	set_long(&philo->mutex_philo, &philo->t_last_meal, gettime(MILLISECOND));
	de_synchronize_philos(philo);
	while (!simulation_finish(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEP, philo);
		precise_usleep(philo->data->t_sleep, philo->data);
		think(philo, false);
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_max_meal == 0)
		return ;
	else if (data->nb_philo == 1)
		safe_thread(&data->philo[0].thread_id, one_philo, &data->philo[0], CREATE);
	else
	{
		while (i < data->nb_philo)
		{
			safe_thread(&data->philo[i].thread_id, dinner_simulation,
				&data->philo[i], CREATE);
			i++;
		}
	}
	safe_thread(&data->monitor, monitor_diner, data, CREATE);
	data->time_start = gettime(MILLISECOND);
	set_bool(&data->mutex_data, &data->all_thread_ready, true);
	i = -1;
	while (++i < data->nb_philo)
		safe_thread(&data->philo[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->mutex_data, &data->end_simulation, true);
	safe_thread(&data->monitor, NULL, NULL, JOIN);
}
