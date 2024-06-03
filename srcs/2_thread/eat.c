/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jangeun-ji <jangeun-ji@student.42seoul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:31 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/03 11:44:19 by jangeun-ji       ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <sys/time.h>

// 포크를 바라보는 새끼가 2명이라서 포크를 붙잡고 안놓으면 더 빨리 먹을 수 있는 새끼가 뒤질 수도 있따.
t_b	available_left_fork(t_pi *info, t_prun *run, int seat)
{
	int				left;
	t_b				res;

	res = FALSE;
	left = seat - 1;
	if (left < 0)
		left = info->philo_num - 1;
	pthread_mutex_lock(&run->fork_mutex[left]);
	if (run->forks[left] == FALSE)
	{
		run->forks[left] = TRUE;
		res = TRUE;
	}
	pthread_mutex_unlock(&run->fork_mutex[left]);
	return (res);
}

t_b	available_right_fork(t_prun *run, int seat)
{
	t_b		res;

	res = FALSE;
	pthread_mutex_lock(&run->fork_mutex[seat]);
	if (run->forks[seat] == FALSE)
	{
		run->forks[seat] = TRUE;
		res = TRUE;
	}
	pthread_mutex_unlock(&run->fork_mutex[seat]);
	return (res);
}

void	put_forks(t_pi *info, t_prun *run, int seat)
{
	int	left;

	left = seat - 1;
	if (left < 0)
		left = info->philo_num - 1;
	pthread_mutex_lock(&run->fork_mutex[left]);
	pthread_mutex_lock(&run->fork_mutex[seat]);
	run->forks[left] = FALSE;
	run->forks[seat] = FALSE;
	pthread_mutex_unlock(&run->fork_mutex[left]);
	pthread_mutex_unlock(&run->fork_mutex[seat]);
}

void	philo_eat(t_pi *info, t_prun *run, int seat)
{
	t_b		left;
	t_b		right;
	long	time;

	time = philo_current(run);
	left = FALSE;
	right = FALSE;
	while (!left || !right)
	{
		if (!left && available_left_fork(info, run, seat))
		{
			left = TRUE;
			philo_printf(info, time, seat, "has taken a fork");
		}
		if (!right && available_right_fork(run, seat))
		{
			philo_printf(info, time, seat, "has taken a fork");
			right = TRUE;
		}
	}
	run->philos[seat].last_eat = time;
	run->philos[seat].count_eat++;
	philo_printf(info, time, seat, "is eating");
	put_forks(info, run, seat);
	philo_delay(run, time, info->eat_to_time);
}
