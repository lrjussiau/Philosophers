/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:46:30 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/24 11:11:53 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}		t_fork;

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

struct s_data
{
	int		nb_philo;
	int		t_eat;
	int		t_sleep;
	int		t_think;
	int		t_die;
	int		nb_max_meal;
	int		time_start;
	bool	end_simulation;
	t_fork	*fork;
	t_philo	*philo;
};

//Utils
void	error(char *str);
long	ft_atol(const char *s);

//Parsing
bool	is_space(char c);
bool	is_digit(char c);
char	*valid_input(char *str);

#endif