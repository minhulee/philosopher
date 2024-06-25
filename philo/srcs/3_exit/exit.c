/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:52 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 11:09:43 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>

void	free_fork(t_fork *fork)
{
	if (!fork)
		return ;
	pthread_mutex_destroy(&fork->fork_mutex);
	free(fork);
	fork = NULL;
}

void	free_philos(t_philo *philos)
{
	int	seat;
	int	philo_num;

	if (!philos)
		return ;
	philo_num = philos->info->philo_num;
	pthread_mutex_destroy(&philos->info->died_mutex);
	pthread_mutex_destroy(&philos->info->print_mutex);
	seat = 0;
	while (seat < philo_num && philos[seat].left)
	{
		free_fork(philos[seat].left);
		seat++;
	}
	free(philos);
	philos = NULL;
}

char	*get_err_message(int errno)
{
	char	*err[ERRMAX];

	err[INVALID_ARGV] = "Error\ninvalid argvs.. : ";
	err[BOOT_TIME_FAIL] = "Error\nget booted time failed.. : ";
	err[INIT_INFO_FAIL] = "Error\ninit info failed.. : ";
	err[OUT_OF_MEMORY] = "Error\nout of memory.. : ";
	err[INIT_FORK_FAIL] = "Error\ninit fork failed.. : ";
	err[PTHREAD_CREATE_FAIL] = "Error\npthread create failed.. : ";
	err[PTHREAD_JOIN_FAIL] = "Error\npthread join failed.. : ";
	err[GET_TIME_FAIL] = "Error\nget time failed.. : ";
	return (err[errno]);
}

void	ft_err(int errno, t_philo *philos)
{
	free_philos(philos);
	printf("%s%d\n", get_err_message(errno), errno);
	exit(1);
}

void	ft_exit(t_philo *philos)
{
	free_philos(philos);
	exit(0);
}
