/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:25:17 by avast             #+#    #+#             */
/*   Updated: 2023/03/29 12:14:46 by avast            ###   ########.fr       */
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

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = 0;
	pthread_mutex_init(&(data->lock_printf), NULL);
}
