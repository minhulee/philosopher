/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:20:29 by minhulee          #+#    #+#             */
/*   Updated: 2024/05/31 09:10:51 by minhulee         ###   ########seoul.kr  */
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