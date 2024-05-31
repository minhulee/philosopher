/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:30 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/31 10:50:30 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "../../lib/ft_printf/ft_printf.h"
#include "../../lib/libft/libft.h"
#include "./philo_err.h"

typedef enum e_bool
{
	FAIL = -1,
	FALSE,
	TRUE
}	t_b;

typedef struct s_philo_wait
{
	atomic_int		ready;
	pthread_mutex_t	ready_mutex;
}	t_pwait;

typedef struct s_philo
{
	int		count_eat;
	long	last_eat;
}	t_p;

typedef struct s_philo_running
{
	pthread_t		*philos_t;
	t_p				*philos;
	long			start;
	t_b				died;
	t_b				*forks;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	printing;
}	t_prun;

typedef struct s_philo_info
{
	int				philo_num;
	int				die_to_time;
	int				eat_to_time;
	int				sleep_to_time;
	int				must_eat;
	t_pwait			wait;
	t_prun			run;
	t_perrno		errno;
}	t_pi;

/* philo_err */
void	exit_err(int errno);

/* parse */
void	parsing(t_pi *info, int ac, char **s);

/* util */
void	philo_delay(t_prun *run, long start, long end);
long	philo_current(t_prun *run);
long	philo_elapsed(t_prun *run, long start);
void	philo_printf(t_pi *info, long time, int seat, char *s);

/* thread */
void	philo(t_pi *info, t_pwait *ready, t_prun *run);
void	*runing(void *av);
void	philo_eat(t_pi *info, t_prun *run, int seat);
void	philo_sleep(t_pi *info, t_prun *run, int seat);
t_b	is_died_philo(t_pi *info, t_prun *run, int seat);

#endif