/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:21 by avast             #+#    #+#             */
/*   Updated: 2023/04/03 14:51:57 by avast            ###   ########.fr       */
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

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->lock_time[i]);
			if (get_time() - data->philo[i].last_meal > data->time_die)
			{
				pthread_mutex_lock(&data->lock_check);
				data->flag_death++;
				pthread_mutex_unlock(&data->lock_check);
				printf_msg(DIED, &data->philo[i]);
			}
			pthread_mutex_unlock(&data->lock_time[i]);
			i++;
		}
		pthread_mutex_lock(&data->lock_check);
		if (data->flag_death)
			break ;
		pthread_mutex_unlock(&data->lock_check);
		i = 0;
		pthread_mutex_lock(&(data->lock_check));
		while (data->meal_max && i < data->nb_philo
			&& data->philo[i].meal_count < data->meal_max)
			i++;
		if (i == data->nb_philo)
		{
			data->flag_eat = 1;
			break ;
		}
		pthread_mutex_unlock(&(data->lock_check));
		usleep(200);
	}
	pthread_mutex_unlock(&(data->lock_check));
	return (0);
}

void	join_and_free(t_data data)
{
	int	i;

	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	free(data.lock_fork);
	free(data.philo);
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
	join_and_free(data);
	return (0);
}
