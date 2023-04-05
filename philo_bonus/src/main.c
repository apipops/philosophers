/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:21 by avast             #+#    #+#             */
/*   Updated: 2023/04/05 15:38:49 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	wait_and_exit(t_data data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < data.nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) < 200)
		{
			i = 0;
			while (i < data.nb_philo)
			{
				kill(data.philo[i].pid, SIGTERM);
				i++;
			}
			printf_msg(DIED, &data.philo[WEXITSTATUS(status)]);
			break ;
		}
		i++;
	}
	free_semaphores(data);
	exit(0);
}

int	free_semaphores(t_data data)
{
	sem_close(data.lock_printf);
	sem_close(data.lock_fork);
	sem_close(data.check_meal);
	sem_close(data.check_death);
	sem_close(data.free_death);
	sem_close(data.total_meals);
	sem_unlink(LOCK_PRINTF);
	sem_unlink(LOCK_FORK);
	sem_unlink(CHECK_MEAL);
	sem_unlink(CHECK_DEATH);
	sem_unlink(FREE_DEATH);
	sem_unlink(TOTAL_MEALS);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6 || !is_valid_arg(av))
		return (write(2, "Invalid arguments.\n", 19), -1);
	if (init_data(&data, ac, av) == -1)
		return (-1);
	data.start_time = get_time();
	if (launch_process(&data) == -1)
		return (-1);
	wait_and_exit(data);
	return (0);
}
