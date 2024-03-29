/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:46:30 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/05 09:42:31 by ljussiau         ###   ########.fr       */
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
	while (is_space(*str))
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
	data->nb_philo = ft_atol(valid_input(av[1]));
	data->t_die = ft_atol(valid_input(av[2])) * 1e3;
	data->t_eat = ft_atol(valid_input(av[3])) * 1e3;
	data->t_sleep = ft_atol(valid_input(av[4])) * 1e3;
	if (av[5])
		data->nb_max_meal = (int)ft_atol(valid_input(av[5]));
	else
		data->nb_max_meal = -1;
	if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60)
		error("You have to give more than 60 ms for each actions");
}
