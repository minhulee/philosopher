/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jangeun-ji <jangeun-ji@student.42seoul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:29 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/03 11:39:55 by jangeun-ji       ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>

void	philo_sleep(t_pi *info, t_prun *run, int seat)
{
	long	time;

	time = philo_current(run);
	philo_printf(info, time, seat, "is sleeping");
	philo_delay(run, time, info->sleep_to_time);
}