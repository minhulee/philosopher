/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:31 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/29 12:43:53 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_b	available_left_fork(t_pi *info)
{
	t_b	flag;

	flag = false;
	lock
	if (forks[philo->i - 1])
		flag = true;
	forks[philo->i - 1] = true;
	unlock
}

// 포크를 바라보는 새끼가 2명이라서 포크를 붙잡고 안놓으면 더 빨리 먹을 수 있는 새끼가 뒤질 수도 있따.
t_b	available_left_fork(t_pi *info)
{
	t_b	flag;
	int	time;

	flag = false;
	time = 0;
	lock
	while (time < 5)
	{
		if (forks[philo->i - 1])
			flag = true;
		forks[philo->i - 1] = true;
		usleep(100);
		time++;
	}
	unlock
}
