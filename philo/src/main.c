/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:21 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 11:13:41 by avast            ###   ########.fr       */
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
	t_philo	*philo;
	int		i;

	philo = NULL;
	if (ac < 5 || ac > 6 || !is_valid_arg(av))
		return (ft_putstr_fd("Invalid arguments.\n", 2), -1);
	if (init_data(&data, ac, av) == -1 || !init_philo(&data, &philo))
		return (ft_putstr_fd("Malloc failed.\n", 2), -1);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	free_data(data, philo);
	return (0);
}
