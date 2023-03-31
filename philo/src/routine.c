/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:38:36 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 11:16:55 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	pthread_mutex_lock(&(philo.data->lock_printf));
	printf("je suis philo #%d\n", philo.index + 1);
	pthread_mutex_unlock(&(philo.data->lock_printf));
	return (NULL);
}
