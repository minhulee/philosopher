/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:56:36 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 11:24:45 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	philo_delay(t_philo philo, long start, long limit)
{
	while (philo_current(philo) - start < limit - 10)
		usleep(1000);
	while (philo_current(philo) - start < limit)
		usleep(100);
}

long	philo_current(t_philo philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		exit(1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - philo.info->booted);
}

void	philo_printf(t_philo philo, char *s)
{
	sem_wait(philo.print);
	printf("%ld %d %s\n", philo_current(philo), philo.seat + 1, s);
	sem_post(philo.print);
}
