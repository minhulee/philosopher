/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:27 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/29 12:05:36 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void	philo_think(t_pi *info, int tid, struct timeval time)
{
	struct timeval	end;
	gettimeofday(&end, NULL);
	pthread_mutex_lock(&info->sleeping);
	printf("%ld %d is sleeping\n", philo_time(time), tid);
	pthread_mutex_unlock(&info->sleeping);
}