/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:30 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 11:09:28 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# include "./philo_exit.h"

typedef enum e_bool
{
	FAIL = -1,
	FALSE,
	TRUE
}	t_b;

typedef struct s_philo_info
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_to_eat;
	long			booted;
	t_b				died;
	pthread_mutex_t	died_mutex;
	pthread_mutex_t	print_mutex;
}	t_p_info;

typedef struct s_fork
{
	t_b				used;
	int				last;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_philo
{
	int				seat;
	pthread_t		philo;
	long			count_eat;
	long			last_eat;
	t_fork			*left;
	t_fork			*right;
	t_p_info		*info;
}	t_philo;

/* philo */
long	get_time(void);
void	ft_mutex_init(pthread_mutex_t *mutex);

/* parse */
void	parsing(t_p_info *info, int ac, char **s);

/* pthread */
void	philo(t_p_info *info);

/* run */
void	*run(void *info);
t_b		ft_died_check(t_philo *philo);
void	ft_eat(t_philo *philo);
void	philo_delay(t_philo *philo, long start, long limit);
long	philo_current(t_philo *philo);
void	philo_printf(t_philo *philo, int seat, char *s);

/* philo_err */
void	ft_exit(t_philo *philos);
void	ft_err(int errno, t_philo *philos);

/* leaks */
void	check(void);

#endif