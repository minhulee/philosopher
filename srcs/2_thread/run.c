/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jangeun-ji <jangeun-ji@student.42seoul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:08:16 by minhulee          #+#    #+#             */
/*   Updated: 2024/06/03 11:40:24 by jangeun-ji       ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

static void	wait_rest_philos(t_pi *info, t_pwait *wait, int *seat)
{
	pthread_mutex_lock(&info->wait.ready_mutex);
	*seat = wait->ready;
	wait->ready++;
	pthread_mutex_unlock(&info->wait.ready_mutex);
	while (1)
	{
		pthread_mutex_lock(&wait->ready_mutex);
		if (wait->ready < 0)
		{
			pthread_mutex_unlock(&wait->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&wait->ready_mutex);
	}
	if (*seat % 2 == 1)
		philo_delay(&info->run, 0, info->eat_to_time);
}

t_b	is_died_philo(t_pi *info, t_prun *run, int seat)
{
	long	current;

	current = philo_current(run);
	pthread_mutex_lock(&run->died_mutex);
	if (info->run.died)
	{
		pthread_mutex_unlock(&run->died_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&run->died_mutex);
	if (philo_elapsed(run, run->philos[seat].last_eat) > info->die_to_time)
	{
		pthread_mutex_lock(&run->died_mutex);
		run->died = TRUE;
		pthread_mutex_unlock(&run->died_mutex);
		philo_printf(info, philo_elapsed(run, current), seat, "died");
		return (TRUE);
	}
	return (FALSE);
}

void	*runing(void *av)
{
	int		seat;
	t_pi	*info;

	info = (t_pi *)av;
	wait_rest_philos(info, &info->wait, &seat);
	while (!info->must_eat || info->run.philos[seat].count_eat < info->must_eat)
	{
		if (is_died_philo(info, &info->run, seat))
			break ;
		philo_eat(info, &info->run, seat);
		if (is_died_philo(info, &info->run, seat))
			break ;
		philo_sleep(info, &info->run, seat);
		if (is_died_philo(info, &info->run, seat))
			break ;
		philo_printf(info, philo_current(&info->run), seat, "is thinking");
	}
	return (NULL);
}