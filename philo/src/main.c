/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:21 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 18:36:09 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	read_data(t_data data)
{
	printf("Nb philo = %d\n", data.nb_philo);
	printf("Time to die = %d\n", data.time_die);
	printf("Time to eat = %d\n", data.time_eat);
	printf("Time to sleep = %d\n", data.time_sleep);
	printf("Nb meal_count = %d\n", data.meal_max);
}

int	check_philo(t_data *data)
{
	int		i;

	while (!data->flag_death)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&(data->lock_check));
			if (get_time() - data->philo[i].last_meal > data->time_die)
				data->flag_death = 1;
			pthread_mutex_unlock(&(data->lock_check));
			usleep(10);
			i++;
		}
		if (data->flag_death)
			break ;
		i = 0;
		while (data->meal_max && i < data->nb_philo
			&& data->philo[i].meal_count < data->meal_max)
			i++;
		if (i == data->nb_philo)
			data->flag_eat = 1;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6 || !is_valid_arg(av))
		return (ft_putstr_fd("Invalid arguments.\n", 2), -1);
	if (init_data(&data, ac, av) == -1)
		return (-1);
	data.start_time = get_time();
	if (launch_threads(&data) == -1)
		return (ft_putstr_fd("Thread init error.\n", 2), -1);
	check_philo(&data);
	free_data(data);
	return (0);
}
