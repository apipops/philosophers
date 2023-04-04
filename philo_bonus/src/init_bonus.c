/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:25:17 by avast             #+#    #+#             */
/*   Updated: 2023/04/04 18:09:22 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

int	init_semaphores(t_data *data)
{
	data->lock_check = sem_open(LOCK_CHECK, O_CREAT, O_RDWR, 1);
	if (data->lock_check == SEM_FAILED)
		return (-1);
	data->lock_printf = sem_open(LOCK_PRINTF, O_CREAT, O_RDWR, 1);
	if (data->lock_check == SEM_FAILED)
		return (sem_close(data->lock_check), -1);
	data->lock_time = sem_open(LOCK_TIME, O_CREAT, O_RDWR, 1);
	if (data->lock_check == SEM_FAILED)
		return (sem_close(data->lock_check), sem_close(data->lock_time), -1);
	data->lock_fork = sem_open(LOCK_FORK, O_CREAT, O_RDWR, data->nb_philo);
	if (data->lock_check == SEM_FAILED)
		return (sem_close(data->lock_check), sem_close(data->lock_time),
			sem_close(data->lock_time), -1);
	return (0);
}

int	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].index = i;
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
	if (init_semaphore(data) == -1)
		return (write(2, "Semaphore creation failed.\n", 27), -1);
	init_philo(data);
	return (0);
}
