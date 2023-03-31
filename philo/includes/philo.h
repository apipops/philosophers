/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:52:28 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 12:31:46 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_max;
	pthread_mutex_t	lock_printf;
	pthread_mutex_t	*lock_fork;
}		t_data;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	int				meals;
	long			start_time;
	pthread_mutex_t	lock_time;
	t_data			*data;
}		t_philo;

/* PARSING */
int		is_valid_arg(char **av);
int		number_length(char *str);
int		init_data(t_data *data, int ac, char **av);
t_philo	**init_philo(t_data *data, t_philo **philo);

/* ROUTINE */
void	*routine(void *arg);

/* UTILS */
void	free_data(t_data data, t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);
long	get_time(void);

#endif