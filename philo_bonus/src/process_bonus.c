/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:37:50 by avast             #+#    #+#             */
/*   Updated: 2023/04/04 18:20:34 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

void	routine_function(t_data *data, t_philo *philo)
{
	while (1)
	{
		sem_wait(data->lock_fork);
		printf_msg(FORK, philo);
		sem_wait(data->lock_fork);
		printf_msg(EATING, philo);
		sem_wait(data->lock_time);
		philo->last_meal = get_time();
		sem_post(data->lock_time);
		sleep_precise(data->time_eat);
		sem_wait(data->lock_check);
		philo->meal_count++;
		sem_post(data->lock_check);
	}
}

int	fork_philo(t_data *data, t_philo *philo)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (write(2, "Fork failed.\n", 13), -1);
	if (pid == 0)
	{
		while (1)
		{
			eat_function(data, philo);
			printf_msg(SLEEPING, philo);
			sleep_precise(data->time_sleep);
			printf_msg(THINKING, philo);
			sleep_precise(1);
			pthread_mutex_lock(&(data->lock_check));
			if (data->flag_death || data->flag_eat)
			{
				pthread_mutex_unlock(&(data->lock_check));
				break ;
			}
			pthread_mutex_unlock(&(data->lock_check));
		}
	}
	philo->pid = pid;
	return (NULL);
}

int	launch_process(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->nb_philo)
	{
		philo[i].last_meal = get_time();
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (-1);
		i++;
	}
	return (0);
}
