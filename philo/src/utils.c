/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:31:51 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 11:06:42 by avast            ###   ########.fr       */
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

void	free_data(t_data data, t_philo *philo)
{
	free(data.lock_fork);
	free(philo);
}
