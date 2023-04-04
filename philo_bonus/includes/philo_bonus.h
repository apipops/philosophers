/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:52:28 by avast             #+#    #+#             */
/*   Updated: 2023/04/04 18:02:49 by avast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

# define LOCK_PRINTF "/lock_printf"
# define LOCK_CHECK "/lock_check"
# define LOCK_TIME "/lock_time"
# define LOCK_FORK "/lock_fork"

typedef struct s_philo
{
	int				index;
	pid_t			pid;
	int				meal_count;
	long long		last_meal;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			meal_max;
	long long	start_time;
	int			flag_death;
	int			flag_eat;
	sem_t		*lock_printf;
	sem_t		*lock_check;
	sem_t		*lock_time;
	sem_t		*lock_fork;
	t_philo		philo[250];
}		t_data;

/* MAIN */
void		check_death(t_data *data);
int			check_philo(t_data *data);
void		join_philo(t_data data);

/* INITIALIZATION */
int			init_data(t_data *data, int ac, char **av);
int			init_semaphores(t_data *data);
int			init_philo(t_data *data);
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
void		sleep_precise(long long timestamp);

#endif