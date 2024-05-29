/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:29 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/29 04:22:00 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>

void	philo_sleep(t_pi *info, int tid, struct timeval time)
{
	struct timeval	end;

	usleep(info->sleep * 1000);
	gettimeofday(&end, NULL);
	pthread_mutex_lock(&info->sleeping);
	printf("%ld %d is sleeping\n", philo_time(time), tid);
	pthread_mutex_unlock(&info->sleeping);
}