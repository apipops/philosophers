/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:52:28 by avast             #+#    #+#             */
/*   Updated: 2023/03/31 18:34:01 by avast            ###   ########.fr       */
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

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meal_max;
	long long		start_time;
	int				flag_death;
	int				flag_eat;
	pthread_mutex_t	lock_printf;
	pthread_mutex_t	lock_check;
	pthread_mutex_t	*lock_fork;
	struct s_philo	*philo;
}		t_data;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	int				left_f;
	int				right_f;
	int				meal_count;
	long long		last_meal;
	t_data			*data;
}		t_philo;

/* MAIN */
int			check_philo(t_data *data);

/* INITIALIZATION */
int			init_data(t_data *data, int ac, char **av);
int			init_mutex(t_data *data);
t_philo		**init_philo(t_data *data, t_philo **philo);
int			is_valid_arg(char **av);
int			number_length(char *str);

/* THREADS */
void		eat_function(t_data *data, t_philo *philo);
int			launch_threads(t_data *data);
void		*routine(void *arg);

/* UTILS */
void		free_data(t_data data);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
long long	get_time(void);
void		printf_msg(int type, t_philo *philo);

#endif