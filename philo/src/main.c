/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:21 by avast             #+#    #+#             */
/*   Updated: 2023/03/29 12:15:27 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	read_data(t_data data)
{
	printf("Nb philo = %d\n", data.nb_philo);
	printf("Time to die = %d\n", data.time_to_die);
	printf("Time to eat = %d\n", data.time_to_eat);
	printf("Time to sleep = %d\n", data.time_to_sleep);
	printf("Nb meals = %d\n", data.nb_meals);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac < 5 || ac > 6 || !is_valid_arg(av))
		return (ft_putstr_fd("Invalid arguments.\n", 2), -1);
	init_data(&data, ac, av);
	i = 0;
	while (i < data.nb_philo)
	{
		
	}
	return (0);
}
