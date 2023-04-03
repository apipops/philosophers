/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:37:50 by avast             #+#    #+#             */
/*   Updated: 2023/04/03 15:06:11 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_function(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->lock_fork[philo->first_f]));
	printf_msg(FORK, philo);
	pthread_mutex_lock(&(data->lock_fork[philo->second_f]));
	printf_msg(EATING, philo);
	pthread_mutex_lock(&(data->lock_time[philo->index]));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(data->lock_time[philo->index]));
	sleep_precise(data->time_eat);
	pthread_mutex_lock(&(data->lock_check));
	philo->meal_count++;
	pthread_mutex_unlock(&(data->lock_check));
	pthread_mutex_unlock(&(data->lock_fork[philo->second_f]));
	pthread_mutex_unlock(&(data->lock_fork[philo->first_f]));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	// Condition pour eviter les deadlocks
	if (philo->index % 2 == 0)
		usleep(1000);
	// en fonction de time to die ? : 0 ttd * 2 
	while (1)
	{
		// Manger
		eat_function(data, philo);

		// Dormir
		printf_msg(SLEEPING, philo);
		sleep_precise(data->time_sleep);
		
		// Penser
		printf_msg(THINKING, philo);
		usleep(1000);

		pthread_mutex_lock(&(data->lock_check));
		if (data->flag_death || data->flag_eat)
		{
			pthread_mutex_unlock(&(data->lock_check));
			break ;
		}
		pthread_mutex_unlock(&(data->lock_check));
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
		//pthread_mutex_lock(&(data->lock_check));
		philo[i].last_meal = get_time();
		//pthread_mutex_unlock(&(data->lock_check));
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (-1);
		i++;
	}
	return (0);
}
