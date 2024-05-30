/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:31 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/30 17:26:55 by minhulee         ###   ########seoul.kr  */
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
		philo_printf(info, philo_current(run), seat, "has taken a fork");
		run->forks[left] = TRUE;
		res = TRUE;
	}
	else
		pthread_mutex_unlock(&run->fork_mutex[left]);
	return (res);
}

t_b	available_right_fork(t_pi *info, t_prun *run, int seat)
{
	t_b		res;

	res = FALSE;
	pthread_mutex_lock(&run->fork_mutex[seat]);
	if (run->forks[seat] == FALSE)
	{
		philo_printf(info, philo_current(run), seat, "has taken a fork");
		run->forks[seat] = TRUE;
		res = TRUE;
	}
	else
		pthread_mutex_unlock(&run->fork_mutex[seat]);
	return (res);
}

void	put_forks(t_pi *info, t_prun *run, int seat)
{
	int	left;

	left = seat - 1;
	if (left < 0)
		left = info->philo_num - 1;
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

	left = FALSE;
	right = FALSE;
	while (!left || !right)
	{
		if (!left && available_left_fork(info, run, seat))
			left = TRUE;
		if (!right && available_right_fork(info, run, seat))
			right = TRUE;
	}
	time = philo_current(run);
	philo_printf(info, time, seat, "is eating");
	while (philo_elapsed(run, time) < info->eat_to_time)
		usleep(10);
	put_forks(info, run, seat);
}
