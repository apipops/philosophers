/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:37:50 by avast             #+#    #+#             */
/*   Updated: 2023/04/05 16:09:39 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*check_philo(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		//printf("address of check_death %p\n", data->check_death);
		sem_wait(data->check_death);
		if ((get_time() - philo->last_meal) >= data->time_die)
		{
			sem_post(data->check_death);
			//printf("je passe ici car je meurs et mon index est %d\n", philo->index);
			sem_post(data->free_death);
			printf_msg(DIED, philo);
			//exit (philo->index);
		}
		(sem_post(data->check_death), sem_wait(data->check_meal));
		if (data->meal_max && philo->meal_count >= data->meal_max)
			sem_post(data->total_meals);
		if (data->meal_max && data->total_meals->__align == data->meal_max)
			(sem_post(data->check_meal), exit (201));
		(sem_post(data->check_meal), sleep_precise(100));
	}
}

void	*exit_death(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	sem_wait(data->free_death);
	sem_post(data->check_death);
	free_semaphores(*data);
	pthread_
	exit(philo->index);
}

void	eat_function(t_data *data, t_philo *philo)
{
	sem_wait(data->lock_fork);
	printf_msg(FORK, philo);
	sem_wait(data->lock_fork);
	printf_msg(EATING, philo);
	sem_wait(data->check_death);
	philo->last_meal = get_time();
	sem_post(data->check_death);
	sleep_precise(data->time_eat);
	sem_wait(data->check_meal);
	philo->meal_count++;
	sem_post(data->check_meal);
	sem_post(data->lock_fork);
	sem_post(data->lock_fork);
}

int	fork_philo(t_data *data, t_philo *philo, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (write(2, "Fork failed.\n", 13), -1);
	if (pid == 0)
	{
		pthread_create(&philo->thread_check, NULL, &check_philo, &philo[i]);
		pthread_create(&philo->thread_free, NULL, &exit_death, &philo[i]);
		if (i % 2 == 0)
			sleep_precise(1);
		while (1)
		{
			eat_function(data, &philo[i]);
			printf_msg(SLEEPING, &philo[i]);
			sleep_precise(data->time_sleep);
			printf_msg(THINKING, &philo[i]);
			sleep_precise(1);
		}
	}
	philo[i].pid = pid;
	return (0);
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
		if (fork_philo(data, philo, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
