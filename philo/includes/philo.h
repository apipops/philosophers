/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:52:28 by avast             #+#    #+#             */
/*   Updated: 2023/03/29 12:21:02 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	pthread_mutex_t	lock_printf;
}		t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	struct s_philo	*right;
	struct s_philo	*left;
}		t_philo;

/* PARSING */
int		is_valid_arg(char **av);
int		number_length(char *str);
void	init_data(t_data *data, int ac, char **av);

/* UTILS */
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);

#endif