/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:25:17 by avast             #+#    #+#             */
/*   Updated: 2023/04/04 16:07:56 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_valid_arg(char **av)
{
	int	i;
	int	j;
	int	flag_positive;

	i = 1;
	while (av[i])
	{
		if (number_length(av[i]) > 11 || av[i][0] == '\0')
			return (0);
		j = 0;
		flag_positive = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			if (av[i][j] > '0' && av[i][j] <= '9')
				flag_positive = 1;
			j++;
		}
		if (!flag_positive)
			return (0);
		i++;
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init(&(data->lock_printf), NULL);
	pthread_mutex_init(&(data->lock_check), NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&(data->lock_fork[i]), NULL);
		pthread_mutex_init(&(data->lock_time[i]), NULL);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].index = i;
		if (i == data->nb_philo - 1)
		{
			data->philo[i].first_f = 0;
			data->philo[i].second_f = i;
		}
		else
		{
			data->philo[i].first_f = i;
			data->philo[i].second_f = i + 1;
		}
		data->philo[i].meal_count = 0;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo < 2 || data->nb_philo > 250)
		return (write(2, "Invalid arguments.\n", 19), -1);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meal_max = ft_atoi(av[5]);
	else
		data->meal_max = 0;
	data->flag_death = 0;
	data->flag_eat = 0;
	init_mutex(data);
	init_philo(data);
	return (0);
}
