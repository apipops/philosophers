/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:25:17 by avast             #+#    #+#             */
/*   Updated: 2023/04/05 15:35:11 by avast            ###   ########.fr       */
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
	sem_unlink(CHECK_MEAL);
	sem_unlink(LOCK_PRINTF);
	sem_unlink(CHECK_DEATH);
	sem_unlink(LOCK_FORK);
	sem_unlink(TOTAL_MEALS);
	sem_unlink(FREE_DEATH);
	data->lock_printf = sem_open(LOCK_PRINTF, O_CREAT, S_IRWXO, 1);
	data->lock_fork = sem_open(LOCK_FORK, O_CREAT, S_IRWXO, data->nb_philo);
	data->check_death = sem_open(CHECK_DEATH, O_CREAT, S_IRWXO, 1);
	data->check_meal = sem_open(CHECK_MEAL, O_CREAT, S_IRWXO, 1);
	data->total_meals = sem_open(CHECK_MEAL, O_CREAT, S_IRWXO, 0);
	data->free_death = sem_open(CHECK_MEAL, O_CREAT, S_IRWXO, 0);
	if (data->lock_printf == SEM_FAILED || data->lock_fork == SEM_FAILED
		|| data->check_death == SEM_FAILED || data->check_meal == SEM_FAILED
		|| data->total_meals == SEM_FAILED || data->free_death == SEM_FAILED)
		return (-1);
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
	if (data->nb_philo < 2 || data->nb_philo > 200)
		return (write(2, "Invalid arguments.\n", 19), -1);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meal_max = ft_atoi(av[5]);
	else
		data->meal_max = 0;
	if (init_semaphores(data) == -1)
		return (write(2, "Semaphore creation failed.\n", 27), -1);
	init_philo(data);
	return (0);
}
