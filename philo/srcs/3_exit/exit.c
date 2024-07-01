/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:39:52 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 10:44:20 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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

char	*get_err_message(t_perrno errno)
{
	char	*err[ERRMAX];

	err[INVALID_ARGV] = "Error\ninvalid argvs.. : ";
	err[BOOT_TIME_FAIL] = "Error\nget booted time failed.. : ";
	err[INIT_INFO_FAIL] = "Error\ninit info failed.. : ";
	err[INIT_PHILO_FAIL] = "Error\ninit philo faild : ";
	err[INIT_FORK_FAIL] = "Error\ninit fork failed.. : ";
	err[CREATE_PTHREAD_FAIL] = "Error\ncreate pthread fail.. : ";
	err[GET_TIME_FAIL] = "Error\nget time failed.. : ";
	return (err[errno]);
}

t_perrno	ft_err(t_perrno errno, t_philo *philos)
{
	free_philos(philos);
	printf("%s%d\n", get_err_message(errno), errno);
	return (errno);
}

int	ft_exit(t_philo *philos)
{
	free_philos(philos);
	return (0);
}
