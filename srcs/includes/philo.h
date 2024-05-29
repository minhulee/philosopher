/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:30 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/29 04:19:13 by minhulee         ###   ########seoul.kr  */
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

typedef struct s_philo_info
{
	int				philo;
	int				dead;
	int				eat;
	int				sleep;
	int				must;
	struct timeval	start_time;
	int				ready;
	pthread_mutex_t	ready_mutex;
	pthread_t		*philos;
	t_b				*forks;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	sleeping;
	pthread_mutex_t	thinking;
	t_perrno		errno;
}	t_pi;

/* philo_err */
void	exit_err(int errno);

/* parse */
void	parsing(t_pi *info, int ac, char **s);

/* thread */
void	new_thread(t_pi *info);
long	philo_time(struct timeval start);
void	philo_sleep(t_pi *info, int tid, struct timeval time);

#endif