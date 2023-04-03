/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:31:51 by avast             #+#    #+#             */
/*   Updated: 2023/04/03 13:30:55 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || fd > 4096 || s == 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	ft_atoi(const char *nptr)
{
	long int	i;
	long int	sign;
	long int	n;

	i = 0;
	sign = 1;
	n = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}	
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + nptr[i] - 48;
		i++;
	}
	return ((int)(n * sign));
}

long long	get_time(void)
{
	struct timeval	tp;
	long long		milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	sleep_precise(long long timestamp)
{
	long long	time;

	time = get_time();
	while ((get_time() - time) < timestamp)
		usleep(30);
}

void	printf_msg(int type, t_philo *philo)
{

	//pthread_mutex_lock(&(philo->data->lock_check));
	if (type != DIED)
	{
		pthread_mutex_lock(&(philo->data->lock_printf));
		printf("%lld ", get_time() - philo->data->start_time);
		printf("%d ", philo->index + 1);
		if (type == FORK)
			printf("has taken a fork\n");
		else if (type == EATING)
			printf("is eating\n");
		else if (type == SLEEPING)
			printf("is sleeping\n");
		else if (type == THINKING)
			printf("is thinking\n");
		pthread_mutex_unlock(&(philo->data->lock_printf));
	}
	else if (type == DIED)
	{
		pthread_mutex_lock(&(philo->data->lock_printf));
		printf("%lld ", get_time() - philo->data->start_time);
		printf("%d died\n", philo->index + 1);
		pthread_mutex_unlock(&(philo->data->lock_printf));
	}
	//pthread_mutex_unlock(&(philo->data->lock_check));
}
