/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 07:53:47 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 10:51:05 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	safe_mutex(&philo->right_fork->fork, LOCK);
	write_status(TAKE_RIGHT_FORK, philo);
	safe_mutex(&philo->left_fork->fork, LOCK);
	write_status(TAKE_LEFT_FORK, philo);
	set_long(&philo->mutex_philo, &philo->t_last_meal, MILLISECOND);
	philo->nb_meal++;
	write_status(EAT, philo);
	precise_usleep(philo->data->t_eat, philo->data);
	if (philo->data->nb_max_meal > 0
		&& philo->nb_meal == philo->data->nb_max_meal)
		set_bool(&philo->mutex_philo, &philo->full, true);
	safe_mutex(&philo->right_fork->fork, UNLOCK);
	safe_mutex(&philo->left_fork->fork, UNLOCK);
}

static void	think(t_philo *philo)
{
	write_status(THINK, philo);
}

static void	*dinner_simulation(void *dt)
{
	t_philo	*philo;

	philo = (t_philo *)dt;
	wait_all_threads(philo->data);
	while (!simulation_finish(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEP, philo);
		precise_usleep(philo->data->t_sleep, philo->data);
		think(philo);
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_max_meal == 0)
	{
		return ;
	}
	else if (data->nb_philo == 1)
		printf("OK\n");
		// handle_one();
	else
	{
		while (i < data->nb_philo)
		{
			safe_thread(&data->philo[i].thread_id, dinner_simulation,
				&data->philo[i], CREATE);
			i++;
		}
	}
	data->time_start = gettime(MILLISECOND);
	printf("%ld\n", data->time_start);
	set_bool(&data->mutex_data, &data->all_thread_ready, true);
	i = 0;
	while (i < data->nb_philo)
	{
		safe_thread(&data->philo[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
