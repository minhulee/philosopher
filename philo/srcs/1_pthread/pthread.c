/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:17:36 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/25 12:01:24 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_fork	*init_left_fork(t_philo *philos, int seat)
{
	t_fork	*left;

	left = (t_fork *)malloc(sizeof(t_fork) * 1);
	if (!left)
	{
		philos[seat].left = NULL;
		ft_err(OUT_OF_MEMORY, (void *)philos);
	}
	left->used = FALSE;
	left->last = -1;
	if (philos[seat].seat % 2 == 1)
		left->last = philos[seat].seat;
	else
		left->last = -1;
	if (pthread_mutex_init(&left->fork_mutex, NULL) == FAIL)
	{
		free(left);
		philos[seat].left = NULL;
		ft_err(INIT_FORK_FAIL, (void *)philos);
	}
	return (left);
}

static void	init_philos(t_philo **philos, t_p_info *info)
{
	int	seat;

	(*philos) = (t_philo *)malloc(info->philo_num * sizeof(t_philo));
	if (!*philos)
		ft_err(OUT_OF_MEMORY, (void *)*philos);
	memset(*philos, 0, info->philo_num * sizeof(t_philo));
	seat = 0;
	while (seat < info->philo_num)
	{
		(*philos)[seat].seat = seat;
		(*philos)[seat].count_eat = 0;
		(*philos)[seat].info = info;
		(*philos)[seat].left = init_left_fork(*philos, seat);
		if (seat != 0)
			(*philos)[seat - 1].right = (*philos)[seat].left;
		seat++;
	}
	(*philos)[seat - 1].right = (*philos)[0].left;
}

static void	new_thread(t_philo *philos)
{
	int	seat;
	int	philo_num;

	philo_num = philos[0].info->philo_num;
	seat = 0;
	while (seat < philo_num)
	{
		philos[seat].last_eat = get_time() - philos->info->booted;
		if (pthread_create(&philos[seat].philo, NULL, run,
				(void *)&philos[seat]) == FAIL)
			exit(1);
		seat++;
	}
	seat = 0;
	while (seat < philo_num)
	{
		if (pthread_join(philos[seat].philo, NULL) == FAIL)
			exit(1);
		seat++;
	}
}

void	philo(t_p_info *info)
{
	t_philo	*philos;

	philos = NULL;
	init_philos(&philos, info);
	new_thread(philos);
	ft_exit(philos);
}
