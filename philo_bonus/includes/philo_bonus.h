/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avast <avast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:52:28 by avast             #+#    #+#             */
/*   Updated: 2023/04/05 15:32:36 by avast            ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

# define LOCK_PRINTF "/lock_printf"
# define CHECK_MEAL "/check_meal"
# define CHECK_DEATH "/check_death"
# define LOCK_FORK "/lock_fork"
# define TOTAL_MEALS "/total_meals"
# define FREE_DEATH "/free_death"

typedef struct s_philo
{
	int				index;
	pid_t			pid;
	pthread_t		thread_check;
	pthread_t		thread_free;
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
	sem_t		*lock_printf;
	sem_t		*lock_fork;
	sem_t		*check_meal;
	sem_t		*check_death;
	sem_t		*total_meals;
	sem_t		*free_death;
	t_philo		philo[200];
}		t_data;

/* MAIN */
int			free_semaphores(t_data data);
void		wait_and_exit(t_data data);

/* INITIALIZATION */
int			init_data(t_data *data, int ac, char **av);
int			init_semaphores(t_data *data);
int			init_philo(t_data *data);
int			is_valid_arg(char **av);
int			number_length(char *str);

/* PROCESS */
void		*check_philo(void *arg);
int			fork_philo(t_data *data, t_philo *philo, int i);
void		eat_function(t_data *data, t_philo *philo);
int			launch_process(t_data *data);

/* UTILS */
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
long long	get_time(void);
void		printf_msg(int type, t_philo *philo);
void		sleep_precise(long long timestamp);

#endif