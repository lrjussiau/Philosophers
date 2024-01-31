/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:54:23 by ljussiau          #+#    #+#             */
/*   Updated: 2024/01/24 10:55:57 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str)
{
	printf("Error : %s\n", str);
	exit (EXIT_FAILURE);
}

long	ft_atol(const char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (s[i] && is_space(s[i]))
		i++;
	if (!s[i])
		return (0);
	if (s[i] == '+')
		i++;
	while (s[i] && is_digit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res);
}