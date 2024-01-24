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

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parsing(&data, av);
		init(&data);
		simulation(&data);
		end_simulation(&data);
	}
	else
	{
		ft_error("Wrong Input.");
	}
	return (0);
}
