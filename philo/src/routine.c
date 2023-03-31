/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:38:36 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 12:54:26 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// Set up le temps
		pthread_mutex_lock(&(philo->lock_time));
		philo->start_time = get_time();
		pthread_mutex_unlock(&(philo->lock_time));

		// Condition pour eviter les deadlocks
		if (philo->index % 2 == 0 && philo->data->nb_philo > 1)
			usleep(5 * 1000);
		if (philo->index % 2 == 1 && philo->index == philo->data->nb_philo - 1)
			usleep(5 * 1000);

		// Prendre une premiere fourchette : la gauche
		pthread_mutex_lock(&(philo->data->lock_fork[philo->index]));
		pthread_mutex_lock(&(philo->data->lock_printf));
		printf("Philo #%d has taken a fork\n", philo->index + 1);
		pthread_mutex_unlock(&(philo->data->lock_printf));

		// Prendre deuxieme fork : la droite
		pthread_mutex_lock(&(philo->data->lock_fork[(philo->index + 1) % philo->data->nb_philo]));
		pthread_mutex_lock(&(philo->data->lock_printf));
		printf("Philo #%d is eating\n", philo->index + 1);
		pthread_mutex_unlock(&(philo->data->lock_printf));
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&(philo->data->lock_fork[philo->index]));
		pthread_mutex_unlock(&(philo->data->lock_fork[(philo->index + 1) % philo->data->nb_philo]));
		philo->meals++;
		if (philo->data->meal_max && philo->meals > philo->data->meal_max)
		{
			pthread_mutex_lock(&(philo->data->lock_printf));
			printf("Sortie de #%d\n", philo->index + 1);
			pthread_mutex_unlock(&(philo->data->lock_printf));
			break ;
		}

		// Dormir
		pthread_mutex_lock(&(philo->data->lock_printf));
		printf("Philo #%d is sleeping\n", philo->index + 1);
		pthread_mutex_unlock(&(philo->data->lock_printf));
		usleep(philo->data->time_to_sleep * 1000);
		
		// Penser
		pthread_mutex_lock(&(philo->data->lock_printf));
		printf("Philo #%d is thiking\n", philo->index + 1);
		pthread_mutex_unlock(&(philo->data->lock_printf));
		usleep(5 * 1000);

	}
	return (NULL);
}
