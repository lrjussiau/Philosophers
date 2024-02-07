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

static void philo_init(t_data *data)
{
    int     i;
    t_philo *philo;

    i = 0;
    while (i < data->nb_philo)
    {
        philo = data->philo + i;
        philo->id = i;
        philo->nb_meal = 0;
        philo->full = false;
        philo->data = data;
        
        
    }
}

typedef struct s_philo
{
	int			id;
	int			nb_meal;
	bool		full;
	int			t_last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}		t_philo;

void    init(t_data *data)
{
    int i;

    i = 0;
    data->end_simulation = false;
    data->philo = safe_malloc(sizeof(t_philo) * data->nb_philo);
    data->fork = safe_malloc(sizeof(t_fork) * data->nb_philo);
    while(i < data->nb_philo)
    {
        safe_mutex(&data->fork[i].fork, INIT);
        data->fork[i].id = i;
        i++;
    }
    philo_init(data);
}