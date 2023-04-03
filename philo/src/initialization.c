/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:25:17 by avast             #+#    #+#             */
/*   Updated: 2023/04/03 14:45:15 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	number_length(char *str)
{
	int	len;

	if (str == 0 || *str == 0)
		return (0);
	while (*str == '0')
		str++;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

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
	data->lock_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->lock_fork)
		return (ft_putstr_fd("Malloc failed.\n", 2), -1);
	data->lock_time = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->lock_time)
		return (free(data->lock_fork), ft_putstr_fd("Malloc failed.\n", 2), -1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&(data->lock_fork[i]), NULL);
		pthread_mutex_init(&(data->lock_time[i]), NULL);
		i++;
	}
	return (0);
}

t_philo	**init_philo(t_data *data, t_philo **philo)
{
	int		i;

	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philo)
		return (ft_putstr_fd("Malloc failed.\n", 2), NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philo)[i].index = i;
		if (i == data->nb_philo - 1)
		{
			(*philo)[i].first_f = 0;
			(*philo)[i].second_f = i;
		}
		else
		{
			(*philo)[i].first_f = i;
			(*philo)[i].second_f = i + 1;
		}
		(*philo)[i].meal_count = 0;
		(*philo)[i].data = data;
		i++;
	}
	return (philo);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo < 2 || data->nb_philo > 500)
		return (ft_putstr_fd("Invalid arguments.\n", 2), -1);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meal_max = ft_atoi(av[5]);
	else
		data->meal_max = 0;
	data->flag_death = 0;
	data->flag_eat = 0;
	if (init_mutex(data) == -1)
		return (-1);
	data->philo = NULL;
	if (!init_philo(data, &(data->philo)))
		return (-1);
	return (0);
}
