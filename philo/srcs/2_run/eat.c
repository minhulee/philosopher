/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:27 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/23 18:51:08 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	down_forks(t_philo *philo)
{
	if (philo->seat % 2 == 0)
	{
		pthread_mutex_lock(&philo->right->fork_mutex);
		philo->right->used = FALSE;
		pthread_mutex_unlock(&philo->right->fork_mutex);
		pthread_mutex_lock(&philo->left->fork_mutex);
		philo->left->used = FALSE;
		pthread_mutex_unlock(&philo->left->fork_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->left->fork_mutex);
		philo->left->used = FALSE;
		pthread_mutex_unlock(&philo->left->fork_mutex);
		pthread_mutex_lock(&philo->right->fork_mutex);
		philo->right->used = FALSE;
		pthread_mutex_unlock(&philo->right->fork_mutex);
	}
}

t_b	put_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	if (fork->used == FALSE && (fork->last < 0 || fork->last != philo->seat))
	{
		fork->used = TRUE;
		fork->last = philo->seat;
		philo_printf(philo, philo->seat, "has taken a fork");
		pthread_mutex_unlock(&fork->fork_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&fork->fork_mutex);
	return (FALSE);
}

t_b	put_forks(t_philo *philo, t_fork *f1, t_fork *f2)
{
	while (!put_fork(philo, f1))
	{
		if (ft_died_check(philo))
			return (FALSE);
		usleep(100);
	}
	while (!put_fork(philo, f2))
	{
		if (ft_died_check(philo))
			return (FALSE);
		usleep(100);
	}
	return (TRUE);
}

void	ft_eat(t_philo *philo)
{
	long	current;

	if (philo->seat % 2 == 0)
	{
		if (!put_forks(philo, philo->right, philo->left))
			return ;
	}
	else
	{
		if (!put_forks(philo, philo->left, philo->right))
			return ;
	}
	current = philo_current(philo);
	philo_printf(philo, philo->seat, "is eating");
	philo->count_eat++;
	philo->last_eat = philo_current(philo);
	philo_delay(philo, current, philo->info->time_to_eat);
	down_forks(philo);
}
