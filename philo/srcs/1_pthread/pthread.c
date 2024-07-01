/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhulee <minhulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:17:36 by minhulee          #+#    #+#             */
/*   Updated: 2024/07/01 10:38:51 by minhulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_b	init_left_fork(t_philo *philos, int seat)
{
	t_fork	*left;

	left = (t_fork *)malloc(sizeof(t_fork));
	if (!left)
	{
		philos[seat].left = NULL;
		return (FALSE);
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
		return (FALSE);
	}
	philos[seat].left = left;
	return (TRUE);
}

t_perrno	init_philos(t_philo **philos, t_p_info *info)
{
	int	seat;

	(*philos) = (t_philo *)malloc(info->philo_num * sizeof(t_philo));
	if (!*philos)
		return (INIT_PHILO_FAIL);
	memset(*philos, 0, info->philo_num * sizeof(t_philo));
	seat = 0;
	while (seat < info->philo_num)
	{
		(*philos)[seat].seat = seat;
		(*philos)[seat].count_eat = 0;
		(*philos)[seat].info = info;
		if (!init_left_fork(*philos, seat))
			return (INIT_PHILO_FAIL);
		if (0 < seat)
			(*philos)[seat - 1].right = (*philos)[seat].left;
		seat++;
	}
	(*philos)[seat - 1].right = (*philos)[0].left;
	return (OK);
}

t_perrno	start_philo(t_philo *philos, int seat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos->info->start_mutex);
	if (seat == philos->info->philo_num)
		philos->info->start = TRUE;
	else
		philos->info->start = FAIL;
	pthread_mutex_unlock(&philos->info->start_mutex);
	while (i < seat)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
	if (seat != philos->info->philo_num)
		return (CREATE_PTHREAD_FAIL);
	return (OK);
}

t_perrno	philo(t_philo *philos)
{
	int	seat;
	int	philo_num;

	philo_num = philos->info->philo_num;
	seat = 0;
	while (seat < philo_num)
	{
		if (pthread_create(&philos[seat].philo, NULL, run,
				(void *)&philos[seat]) == FAIL)
			break ;
		seat++;
	}
	if (start_philo(philos, seat) != OK)
		return (CREATE_PTHREAD_FAIL);
	return (OK);
}
