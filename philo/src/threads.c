/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:37:50 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 18:58:23 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_function(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->lock_fork[philo->left_f]));
	printf_msg(FORK, philo);
	pthread_mutex_lock(&(data->lock_fork[philo->right_f]));
	printf_msg(EATING, philo);
	pthread_mutex_lock(&(data->lock_check));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(data->lock_check));
	usleep(data->time_eat * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(&(data->lock_fork[philo->left_f]));
	pthread_mutex_unlock(&(data->lock_fork[philo->right_f]));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		// Condition pour eviter les deadlocks
		if (philo->index % 2 == 0)
			usleep(20);
		if (philo->index % 2 == 1 && philo->index == philo->data->nb_philo - 1)
			usleep(20);

		// Manger
		eat_function(data, philo);
		if (data->flag_death)
			break ;

		// Dormir
		printf_msg(SLEEPING, philo);
		usleep(data->time_sleep * 1000);
		
		// Penser
		printf_msg(THINKING, philo);
		usleep(15);

	}
	return (NULL);
}

int	launch_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&(data->lock_check));
		philo->last_meal = get_time();
		pthread_mutex_unlock(&(data->lock_check));
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (-1);
		i++;
	}
	return (0);
}
