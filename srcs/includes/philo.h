/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:30 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/30 17:04:25 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int	ready;
	t_b	start;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	start_mutex;
}	t_pwait;

typedef struct s_philo_running
{
	long			start;
	t_b				*forks;
	t_b				died;
	pthread_t		*philos;
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

/* thread */
void	philo(t_pi *info, t_pwait *ready, t_prun *run);
void	philo_delay(t_pi *info, t_prun *run, int c);
long	philo_current(t_prun *run);
long	philo_elapsed(t_prun *run, long start);
void	philo_printf(t_pi *info, long time, int seat, char *s);
void	philo_eat(t_pi *info, t_prun *run, int seat);
void	philo_sleep(t_pi *info, t_prun *run, int seat);

#endif