/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:52:04 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/24 11:36:02 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <sys/semaphore.h>

//t_b		ft_died_check(t_philo *philo)
//{
//	sem_wait(philo->died);
//	if (philo->kill)
//	{
//		sem_post(philo->died);
//		return (TRUE);
//	}
//	sem_post(philo->died);
//	return (FALSE);
//}

void	ft_sleep(t_philo *philo)
{
	long	current;

	current = philo_current(philo);
	philo_printf(philo, "is sleeping");
	philo_delay(philo, current, philo->info->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	long	current;

	current = philo_current(philo);
	philo_printf(philo, "is eating");
	philo->count_eat++;
	sem_wait(philo->died);
	philo->last_eat = current;
	sem_post(philo->died);
	philo_delay(philo, current, philo->info->time_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
}

t_b	get_fork(t_philo *philo)
{
	if (philo->info->philo_num == 1)
	{
		sem_wait(philo->fork);
		philo_printf(philo, "has taken a fork");
		sem_post(philo->fork);
	}
	sem_wait(philo->fork);
	philo_printf(philo, "has taken a fork");
	sem_wait(philo->fork);
	philo_printf(philo, "has taken a fork");
	return (TRUE);
}

void	run(t_philo *philo)
{
	pthread_t	moniter;

	pthread_create(&moniter, NULL, monitering, (void *)philo);
	while (philo->info->must_to_eat < 0
		|| philo->count_eat < philo->info->must_to_eat)
	{
		get_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		philo_printf(philo, "is thinking");
	}
	exit(0);
	return ;
}
