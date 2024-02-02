/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:54:23 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/02 11:03:19 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error("Gettimeofday failed");
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error("Wrong input to gettime:");
	return (0);
}

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

void	precise_usleep(int usec, t_data *data)
{
	int	start;
	int	laps;
	int	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finish(data))
			break ;
		laps = gettime(MICROSECOND) - start;
		rem = usec - laps;
		if (rem > 1e3)
			usleep(usec / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
			{
				continue ;
			}
	}
}
