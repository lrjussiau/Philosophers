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

#include "philo.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	check_len(char	*str)
{
	return (ft_atol(str) < INT_MAX);
}

char	*valid_input(char *str)
{
	char	*valid;

	valid = NULL;
	while(is_space(*str))
		str++;
	if (*str == '-')
		error("You can not input negative number");
	if (!is_digit(*str))
		error("You have to input number");
	if (check_len(str))
		valid = str;
	return (valid);
}

void	parsing(t_data *data, char **av)
{
	data->nb_philo = (int)ft_atol(valid_input(av[1]));
	data->t_die = (int)ft_atol(valid_input(av[2]));
	data->t_eat = (int)ft_atol(valid_input(av[3]));
	data->t_sleep = (int)ft_atol(valid_input(av[4]));
	if (av[5])
		data->nb_max_meal = (int)ft_atol(valid_input(av[6]));
	else
		data->nb_max_meal = -1;
	if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60)
		error("You have to give more than 60 ms for each actions")
}