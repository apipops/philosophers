/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:21 by avast             #+#    #+#             */
/*   Updated: 2023/04/05 11:02:48 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_death(t_data *data)
{
	int	i;

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
}

int	check_philo(t_data *data)
{
	int		i;

	while (1)
	{
		check_death(data);
		pthread_mutex_lock(&data->lock_check);
		if (data->flag_death)
			break ;
		i = 0;
		while (data->meal_max && i < data->nb_philo
			&& data->philo[i].meal_count >= data->meal_max)
			i++;
		if (i == data->nb_philo)
		{
			data->flag_eat = 1;
			break ;
		}
		pthread_mutex_unlock(&(data->lock_check));
		sleep_precise(1);
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
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_mutex_destroy(&data.lock_fork[i]);
		pthread_mutex_destroy(&data.lock_time[i]);
		i++;
	}
	free(data.philo);
	free(data.lock_fork);
	free(data.lock_time);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6 || !is_valid_arg(av))
		return (write(2, "Invalid arguments.\n", 19), -1);
	if (init_data(&data, ac, av) == -1)
		return (-1);
	data.start_time = get_time();
	if (launch_threads(&data) == -1)
		return (write(2, "Thread creation failed.\n", 24), -1);
	check_philo(&data);
	join_and_free(data);
	return (0);
}
