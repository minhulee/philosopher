/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:41:25 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 10:42:19 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	philo_delay(t_philo *philo, long start, long limit)
{
	while (!ft_died_check(philo)
		&& philo_current(philo) - start < limit - 1)
		usleep(1000);
	while (!ft_died_check(philo)
		&& philo_current(philo) - start < limit)
		usleep(10);
}

void	philo_printf(t_philo *philo, int seat, char *s)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->died_mutex);
	if (philo->info->died)
	{
		pthread_mutex_unlock(&philo->info->print_mutex);
		pthread_mutex_unlock(&philo->info->died_mutex);
		return ;
	}
	printf("%ld %d %s\n", philo_current(philo), seat + 1, s);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_unlock(&philo->info->died_mutex);
}

long	philo_current(t_philo *philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (FAIL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->info->booted);
}
