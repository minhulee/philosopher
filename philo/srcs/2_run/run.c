/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:01:10 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 14:57:09 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_sleep(t_philo *philo)
{
	long	current;

	current = philo_current(philo);
	philo_printf(philo, philo->seat, "is sleeping");
	philo_delay(philo, current, philo->info->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	philo_printf(philo, philo->seat, "is thinking");
}

t_b	ft_died_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->died_mutex);
	if (philo->info->died)
	{
		pthread_mutex_unlock(&philo->info->died_mutex);
		return (TRUE);
	}
	else if (philo_current(philo) - philo->last_eat
		> philo->info->time_to_die)
	{
		philo->info->died = TRUE;
		pthread_mutex_lock(&philo->info->print_mutex);
		printf("%ld %d died\n", philo_current(philo), philo->seat + 1);
		pthread_mutex_unlock(&philo->info->died_mutex);
		return (TRUE);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->died_mutex);
		return (FALSE);
	}
}

void	*run(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	while (philo->info->must_to_eat < 0
		|| philo->count_eat < philo->info->must_to_eat)
	{
		if (ft_died_check(philo))
			break ;
		ft_eat(philo);
		if (ft_died_check(philo))
			break ;
		ft_sleep(philo);
		if (ft_died_check(philo))
			break ;
		ft_think(philo);
	}
	return (NULL);
}
